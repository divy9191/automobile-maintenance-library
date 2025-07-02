class AutomobileMaintenanceApp {
    constructor() {
        this.vehicles = [];
        this.availableTasks = [];
        this.addTaskModal = null;
        this.notificationToast = null;
        
        this.init();
    }

    async init() {
        // Initialize Bootstrap components
        this.addTaskModal = new bootstrap.Modal(document.getElementById('addTaskModal'));
        this.notificationToast = new bootstrap.Toast(document.getElementById('notificationToast'));

        // Set up event listeners
        this.setupEventListeners();

        // Load initial data
        await this.loadVehicles();
        await this.loadAvailableTasks();
        this.updateDashboard();
    }

    setupEventListeners() {
        // Add vehicle form submission
        document.getElementById('addVehicleForm').addEventListener('submit', (e) => {
            e.preventDefault();
            this.addVehicle();
        });

        // Task selection change in modal
        document.getElementById('taskSelect').addEventListener('change', (e) => {
            this.showTaskDescription(e.target.value);
        });
    }

    async loadVehicles() {
        try {
            const response = await fetch('/api/vehicles');
            if (response.ok) {
                this.vehicles = await response.json();
                this.renderVehicles();
            } else {
                this.showNotification('Failed to load vehicles', 'error');
            }
        } catch (error) {
            console.error('Error loading vehicles:', error);
            this.showNotification('Error loading vehicles', 'error');
        }
    }

    async loadAvailableTasks() {
        try {
            const response = await fetch('/api/tasks');
            if (response.ok) {
                this.availableTasks = await response.json();
                this.renderAvailableTasks();
                this.populateTaskSelect();
            } else {
                this.showNotification('Failed to load available tasks', 'error');
            }
        } catch (error) {
            console.error('Error loading tasks:', error);
            this.showNotification('Error loading available tasks', 'error');
        }
    }

    async addVehicle() {
        const formData = new FormData(document.getElementById('addVehicleForm'));
        
        try {
            const response = await fetch('/api/vehicles', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(formData)
            });

            if (response.ok) {
                this.showNotification('Vehicle added successfully!', 'success');
                document.getElementById('addVehicleForm').reset();
                await this.loadVehicles();
                this.updateDashboard();
            } else {
                this.showNotification('Failed to add vehicle', 'error');
            }
        } catch (error) {
            console.error('Error adding vehicle:', error);
            this.showNotification('Error adding vehicle', 'error');
        }
    }

    async removeVehicle(vehicleId) {
        if (!confirm('Are you sure you want to remove this vehicle?')) {
            return;
        }

        try {
            const response = await fetch(`/api/vehicles/${vehicleId}`, {
                method: 'DELETE'
            });

            if (response.ok) {
                this.showNotification('Vehicle removed successfully!', 'success');
                await this.loadVehicles();
                this.updateDashboard();
            } else {
                this.showNotification('Failed to remove vehicle', 'error');
            }
        } catch (error) {
            console.error('Error removing vehicle:', error);
            this.showNotification('Error removing vehicle', 'error');
        }
    }

    showAddTaskModal(vehicleId) {
        document.getElementById('selectedVehicleId').value = vehicleId;
        document.getElementById('taskSelect').value = '';
        document.getElementById('taskDescription').style.display = 'none';
        
        // Filter tasks based on vehicle type
        const vehicle = this.vehicles.find(v => v.id === vehicleId);
        if (vehicle) {
            this.populateTaskSelect(vehicle.type);
        }
        
        this.addTaskModal.show();
    }

    async addTaskToVehicle() {
        const vehicleId = parseInt(document.getElementById('selectedVehicleId').value);
        const taskId = parseInt(document.getElementById('taskSelect').value);

        if (!taskId) {
            this.showNotification('Please select a task', 'error');
            return;
        }

        try {
            const response = await fetch(`/api/vehicles/${vehicleId}/tasks`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: `taskId=${taskId}`
            });

            const result = await response.json();
            if (result.success) {
                this.showNotification('Task added successfully!', 'success');
                this.addTaskModal.hide();
                await this.loadVehicles();
                this.updateDashboard();
            } else {
                this.showNotification('Failed to add task. Task may not be applicable to this vehicle type.', 'error');
            }
        } catch (error) {
            console.error('Error adding task:', error);
            this.showNotification('Error adding task', 'error');
        }
    }

    populateTaskSelect(vehicleType = null) {
        const taskSelect = document.getElementById('taskSelect');
        taskSelect.innerHTML = '<option value="">Choose a maintenance task</option>';

        this.availableTasks.forEach(task => {
            if (!vehicleType || task.applicable.includes(vehicleType)) {
                const option = document.createElement('option');
                option.value = task.id;
                option.textContent = task.name;
                option.dataset.description = task.description;
                option.dataset.applicable = task.applicable.join(', ');
                taskSelect.appendChild(option);
            }
        });
    }

    showTaskDescription(taskId) {
        const descriptionDiv = document.getElementById('taskDescription');
        if (!taskId) {
            descriptionDiv.style.display = 'none';
            return;
        }

        const task = this.availableTasks.find(t => t.id === parseInt(taskId));
        if (task) {
            descriptionDiv.innerHTML = `
                <strong>${task.name}:</strong> ${task.description}<br>
                <small><strong>Applicable to:</strong> ${task.applicable.join(', ')} vehicles</small>
            `;
            descriptionDiv.style.display = 'block';
        }
    }

    renderVehicles() {
        const container = document.getElementById('vehiclesList');
        
        if (this.vehicles.length === 0) {
            container.innerHTML = `
                <div class="empty-state">
                    <i class="fas fa-car"></i>
                    <h5>No vehicles in library</h5>
                    <p class="text-muted">Add your first vehicle using the form above.</p>
                </div>
            `;
            return;
        }

        container.innerHTML = this.vehicles.map(vehicle => `
            <div class="vehicle-card card mb-3 ${vehicle.type} fade-in-up">
                <div class="card-body">
                    <div class="row">
                        <div class="col-md-8">
                            <div class="vehicle-info">
                                <h5 class="card-title">
                                    ${vehicle.year} ${vehicle.make} ${vehicle.model}
                                    <span class="badge bg-${this.getVehicleTypeBadgeColor(vehicle.type)} vehicle-type-badge ms-2">
                                        ${this.getVehicleTypeIcon(vehicle.type)} ${vehicle.type.toUpperCase()}
                                    </span>
                                </h5>
                                <p class="card-text">
                                    <strong>Vehicle ID:</strong> ${vehicle.id}<br>
                                    <strong>Odometer:</strong> ${vehicle.odometer.toLocaleString()} miles
                                </p>
                            </div>
                            
                            <div class="maintenance-tasks">
                                <h6><i class="fas fa-wrench"></i> Maintenance Tasks (${vehicle.tasks.length})</h6>
                                <div class="task-list">
                                    ${vehicle.tasks.length > 0 ? 
                                        vehicle.tasks.map((task, index) => `
                                            <div class="maintenance-task-item">
                                                <strong>${task.name}</strong><br>
                                                <small class="text-muted">${task.description}</small>
                                            </div>
                                        `).join('') :
                                        '<p class="text-muted"><em>No maintenance tasks assigned</em></p>'
                                    }
                                </div>
                            </div>
                        </div>
                        
                        <div class="col-md-4">
                            <div class="vehicle-actions">
                                <button class="btn btn-success btn-sm" onclick="app.showAddTaskModal(${vehicle.id})">
                                    <i class="fas fa-plus"></i> Add Task
                                </button>
                                <button class="btn btn-danger btn-sm" onclick="app.removeVehicle(${vehicle.id})">
                                    <i class="fas fa-trash"></i> Remove Vehicle
                                </button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `).join('');
    }

    renderAvailableTasks() {
        const container = document.getElementById('availableTasks');
        
        if (this.availableTasks.length === 0) {
            container.innerHTML = '<p class="text-muted">No tasks available</p>';
            return;
        }

        container.innerHTML = `
            <div class="task-list">
                ${this.availableTasks.map(task => `
                    <div class="maintenance-task-item">
                        <div class="d-flex justify-content-between align-items-start">
                            <div>
                                <strong>${task.name}</strong><br>
                                <small class="text-muted">${task.description}</small>
                                <div class="applicable-types mt-2">
                                    ${task.applicable.map(type => 
                                        `<span class="type-badge ${type}">${type}</span>`
                                    ).join('')}
                                </div>
                            </div>
                        </div>
                    </div>
                `).join('')}
            </div>
        `;
    }

    updateDashboard() {
        const totalVehicles = this.vehicles.length;
        const electricCount = this.vehicles.filter(v => v.type === 'electric').length;
        const totalTasks = this.vehicles.reduce((sum, vehicle) => sum + vehicle.tasks.length, 0);

        document.getElementById('totalVehicles').textContent = totalVehicles;
        document.getElementById('electricCount').textContent = electricCount;
        document.getElementById('totalTasks').textContent = totalTasks;
    }

    getVehicleTypeBadgeColor(type) {
        switch(type) {
            case 'electric': return 'success';
            case 'gas': return 'warning';
            case 'diesel': return 'info';
            default: return 'secondary';
        }
    }

    getVehicleTypeIcon(type) {
        switch(type) {
            case 'electric': return '<i class="fas fa-bolt"></i>';
            case 'gas': return '<i class="fas fa-gas-pump"></i>';
            case 'diesel': return '<i class="fas fa-tractor"></i>';
            default: return '<i class="fas fa-car"></i>';
        }
    }

    showNotification(message, type = 'info') {
        const toastElement = document.getElementById('notificationToast');
        const toastBody = document.getElementById('toastMessage');
        
        // Set message and styling based on type
        toastBody.textContent = message;
        toastElement.className = `toast ${type === 'success' ? 'bg-success text-white' : 
                                         type === 'error' ? 'bg-danger text-white' : ''}`;

        this.notificationToast.show();
    }
}

// Global app instance
let app;

// Initialize app when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    app = new AutomobileMaintenanceApp();
});

// Global function to make it accessible from HTML onclick handlers
window.addTaskToVehicle = () => app.addTaskToVehicle();
