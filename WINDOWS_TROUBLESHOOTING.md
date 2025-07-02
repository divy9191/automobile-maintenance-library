# Windows Troubleshooting Guide

## "Can't reach this page" Error Solutions

If you get "can't reach this page" when trying to access the server, try these solutions:

### Solution 1: Use the Correct URL
**Don't use:** `http://0.0.0.0:5000`
**Use instead:** `http://localhost:5000` or `http://127.0.0.1:5000`

### Solution 2: Check the Server Output
When you run `maintenance_server.exe`, look for this message:
```
========================================
Server started successfully!
Open your web browser and go to:
  http://localhost:XXXX
  or
  http://127.0.0.1:XXXX
========================================
```
Use the exact URL shown (XXXX will be the port number).

### Solution 3: Port Issues
The server will automatically try different ports if 5000 is blocked:
- First tries port 5000
- Then tries 8080, 3000, 8000, 9000
- Use whatever port it successfully starts on

### Solution 4: Windows Firewall
If the server won't start at all:

1. **Run as Administrator:**
   - Right-click Command Prompt
   - Select "Run as administrator"
   - Navigate to your project folder
   - Run the build and server again

2. **Allow through Windows Firewall:**
   - When you first run the server, Windows may ask for firewall permission
   - Click "Allow access" for both private and public networks

### Solution 5: Check for Conflicts
If you see "Port XXXX is already in use":
- Close other applications that might use the same port
- Or just let the server try the next available port automatically

### Solution 6: Antivirus Software
Some antivirus programs block local servers:
- Temporarily disable real-time protection
- Or add the project folder to antivirus exclusions

## Step-by-Step Verification

1. **Build the project:**
   ```cmd
   build_windows.bat
   ```

2. **Run the server:**
   ```cmd
   cd build
   maintenance_server.exe
   ```

3. **Look for success message:**
   ```
   Server started successfully!
   ```

4. **Copy the exact URL from the output**

5. **Open browser and paste the URL**

## Still Having Issues?

If none of these work:

1. **Check Windows version:** Windows 10/11 recommended
2. **Verify MinGW installation:** Run `gcc --version`
3. **Try a different browser:** Chrome, Firefox, Edge
4. **Restart your computer** and try again

## Alternative Port Testing

You can also test if the server is working by using Command Prompt:
```cmd
curl http://localhost:5000
```
If this returns HTML content, the server is working and it's a browser issue.