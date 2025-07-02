#include "MaintenanceLibrary.h"
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <functional>
#include <cstring>
#include <fstream>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define close closesocket
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif

// Simple HTTP server implementation
class SimpleHTTPServer {
private:
    int server_fd;
    int port;
    MaintenanceLibrary& library;

    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::string urlDecode(const std::string& str) {
        std::string decoded;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '%' && i + 2 < str.length()) {
                int value = std::stoi(str.substr(i + 1, 2), nullptr, 16);
                decoded += static_cast<char>(value);
                i += 2;
            } else if (str[i] == '+') {
                decoded += ' ';
            } else {
                decoded += str[i];
            }
        }
        return decoded;
    }

    std::map<std::string, std::string> parseFormData(const std::string& body) {
        std::map<std::string, std::string> data;
        std::stringstream ss(body);
        std::string pair;
        
        while (std::getline(ss, pair, '&')) {
            size_t eq = pair.find('=');
            if (eq != std::string::npos) {
                std::string key = urlDecode(pair.substr(0, eq));
                std::string value = urlDecode(pair.substr(eq + 1));
                data[key] = value;
            }
        }
        return data;
    }

    std::string jsonEscape(const std::string& str) {
        std::string escaped;
        for (char c : str) {
            switch (c) {
                case '"': escaped += "\\\""; break;
                case '\\': escaped += "\\\\"; break;
                case '\n': escaped += "\\n"; break;
                case '\r': escaped += "\\r"; break;
                case '\t': escaped += "\\t"; break;
                default: escaped += c; break;
            }
        }
        return escaped;
    }

    std::string vehiclesToJson() {
        std::stringstream json;
        json << "[";
        const auto& vehicles = library.getAllVehicles();
        for (size_t i = 0; i < vehicles.size(); ++i) {
            if (i > 0) json << ",";
            json << "{";
            json << "\"id\":" << vehicles[i]->getId() << ",";
            json << "\"make\":\"" << jsonEscape(vehicles[i]->getMake()) << "\",";
            json << "\"model\":\"" << jsonEscape(vehicles[i]->getModel()) << "\",";
            json << "\"year\":" << vehicles[i]->getYear() << ",";
            json << "\"odometer\":" << vehicles[i]->getOdometerReading() << ",";
            json << "\"type\":\"" << jsonEscape(vehicles[i]->getVehicleType()) << "\",";
            json << "\"tasks\":[";
            const auto& tasks = vehicles[i]->getMaintenanceTasks();
            for (size_t j = 0; j < tasks.size(); ++j) {
                if (j > 0) json << ",";
                json << "{";
                json << "\"id\":" << tasks[j]->getId() << ",";
                json << "\"name\":\"" << jsonEscape(tasks[j]->getTaskName()) << "\",";
                json << "\"description\":\"" << jsonEscape(tasks[j]->getDescription()) << "\"";
                json << "}";
            }
            json << "]";
            json << "}";
        }
        json << "]";
        return json.str();
    }

    std::string tasksToJson() {
        std::stringstream json;
        json << "[";
        const auto& tasks = library.getAvailableTasks();
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (i > 0) json << ",";
            json << "{";
            json << "\"id\":" << tasks[i]->getId() << ",";
            json << "\"name\":\"" << jsonEscape(tasks[i]->getTaskName()) << "\",";
            json << "\"description\":\"" << jsonEscape(tasks[i]->getDescription()) << "\",";
            json << "\"applicable\":[";
            const auto& types = tasks[i]->getApplicableVehicleTypes();
            for (size_t j = 0; j < types.size(); ++j) {
                if (j > 0) json << ",";
                json << "\"" << jsonEscape(types[j]) << "\"";
            }
            json << "]";
            json << "}";
        }
        json << "]";
        return json.str();
    }

    std::string handleRequest(const std::string& method, const std::string& path, const std::string& body) {
        std::string response;

        if (method == "GET" && path == "/") {
            std::string content = readFile("public/index.html");
            if (content.empty()) {
                response = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
            } else {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + 
                          std::to_string(content.length()) + "\r\n\r\n" + content;
            }
        }
        else if (method == "GET" && path == "/style.css") {
            std::string content = readFile("public/style.css");
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\nContent-Length: " + 
                      std::to_string(content.length()) + "\r\n\r\n" + content;
        }
        else if (method == "GET" && path == "/app.js") {
            std::string content = readFile("public/app.js");
            response = "HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\nContent-Length: " + 
                      std::to_string(content.length()) + "\r\n\r\n" + content;
        }
        else if (method == "GET" && path == "/api/vehicles") {
            std::string json = vehiclesToJson();
            response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " + 
                      std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        else if (method == "GET" && path == "/api/tasks") {
            std::string json = tasksToJson();
            response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " + 
                      std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        else if (method == "POST" && path == "/api/vehicles") {
            auto data = parseFormData(body);
            std::string type = data["type"];
            std::string make = data["make"];
            std::string model = data["model"];
            int year = std::stoi(data["year"]);
            int odometer = std::stoi(data["odometer"]);

            std::shared_ptr<Automobile> vehicle;
            if (type == "electric") {
                vehicle = std::make_shared<ElectricCar>(make, model, year, odometer);
            } else if (type == "gas") {
                vehicle = std::make_shared<GasCar>(make, model, year, odometer);
            } else if (type == "diesel") {
                vehicle = std::make_shared<DieselCar>(make, model, year, odometer);
            }

            if (vehicle) {
                library.addVehicle(vehicle);
                response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 19\r\n\r\n{\"success\": true}";
            } else {
                response = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nContent-Length: 20\r\n\r\n{\"success\": false}";
            }
        }
        else if (method == "DELETE" && path.substr(0, 14) == "/api/vehicles/") {
            int vehicleId = std::stoi(path.substr(14));
            bool success = library.removeVehicle(vehicleId);
            std::string json = success ? "{\"success\": true}" : "{\"success\": false}";
            response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " + 
                      std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        else if (method == "POST" && path.find("/api/vehicles/") == 0 && path.find("/tasks") != std::string::npos) {
            size_t vehiclePos = path.find("/api/vehicles/") + 14;
            size_t tasksPos = path.find("/tasks");
            int vehicleId = std::stoi(path.substr(vehiclePos, tasksPos - vehiclePos));
            
            auto data = parseFormData(body);
            int taskId = std::stoi(data["taskId"]);
            
            bool success = library.addMaintenanceTaskToVehicle(vehicleId, taskId);
            std::string json = success ? "{\"success\": true}" : "{\"success\": false}";
            response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " + 
                      std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        else {
            response = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
        }

        return response;
    }

public:
    SimpleHTTPServer(int port, MaintenanceLibrary& lib) : port(port), library(lib) {}

    bool start() {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }
#endif

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            std::cerr << "Failed to create socket" << std::endl;
#ifdef _WIN32
            WSACleanup();
#endif
            return false;
        }

        int opt = 1;
#ifdef _WIN32
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
#else
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
#ifdef _WIN32
            int error = WSAGetLastError();
            std::cerr << "Failed to bind to port " << port << " (Windows Error: " << error << ")" << std::endl;
            if (error == WSAEADDRINUSE) {
                std::cerr << "Port " << port << " is already in use. Try a different port or close other applications using this port." << std::endl;
            }
#else
            std::cerr << "Failed to bind to port " << port << std::endl;
#endif
            return false;
        }

        if (listen(server_fd, 10) < 0) {
            std::cerr << "Failed to listen on socket" << std::endl;
            return false;
        }

        std::cout << "========================================" << std::endl;
        std::cout << "Server started successfully!" << std::endl;
        std::cout << "Open your web browser and go to:" << std::endl;
        std::cout << "  http://localhost:" << port << std::endl;
        std::cout << "  or" << std::endl;
        std::cout << "  http://127.0.0.1:" << port << std::endl;
        std::cout << "========================================" << std::endl;
        return true;
    }

    void run() {
        while (true) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            
            if (client_fd < 0) continue;

            char buffer[4096] = {0};
#ifdef _WIN32
            int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
#else
            ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
#endif
            
            if (bytes_read > 0) {
                std::string request(buffer, bytes_read);
                std::stringstream ss(request);
                std::string method, path, version;
                ss >> method >> path >> version;

                std::string body;
                size_t body_start = request.find("\r\n\r\n");
                if (body_start != std::string::npos) {
                    body = request.substr(body_start + 4);
                }

                std::string response = handleRequest(method, path, body);
#ifdef _WIN32
                send(client_fd, response.c_str(), response.length(), 0);
#else
                write(client_fd, response.c_str(), response.length());
#endif
            }

            close(client_fd);
        }
    }

    ~SimpleHTTPServer() {
        if (server_fd != -1) {
            close(server_fd);
        }
#ifdef _WIN32
        WSACleanup();
#endif
    }
};

int main() {
    MaintenanceLibrary library;
    
    // Add some sample vehicles for demonstration
    library.addVehicle(std::make_shared<ElectricCar>("Tesla", "Model 3", 2022, 15000));
    library.addVehicle(std::make_shared<GasCar>("Toyota", "Camry", 2021, 25000));
    library.addVehicle(std::make_shared<DieselCar>("Ford", "F-250", 2020, 45000));

    // Try different ports if 5000 is blocked
    std::vector<int> ports = {5000, 8080, 3000, 8000, 9000};
    
    for (int port : ports) {
        std::cout << "Trying to start server on port " << port << "..." << std::endl;
        SimpleHTTPServer server(port, library);
        
        if (server.start()) {
            std::cout << "Press Ctrl+C to stop the server." << std::endl;
            server.run();
            return 0;
        } else {
            std::cout << "Port " << port << " failed, trying next port..." << std::endl;
        }
    }
    
    std::cerr << "Failed to start server on any available port." << std::endl;
    std::cerr << "This might be a firewall issue. Try running as administrator." << std::endl;
    return 1;
}
