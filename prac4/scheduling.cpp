/*
 * CPU SCHEDULING ALGORITHMS
 * Implementa FCFS, SJF, SRTF, Round Robin y Priority.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué varía según algoritmo?
 *   - FCFS: O(n log n) ordenar por arrival + O(n) simular = O(n log n)
 *   - SJF: O(n²) porque por cada tiempo busca proceso más corto disponible
 *   - SRTF: O(n·T) revisa todos los procesos en cada unidad de tiempo T
 *   - Round Robin: O(n·T/q) donde q=quantum, peor con quantum pequeño
 *   - Priority: O(n²) similar a SJF pero busca mayor prioridad
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   FCFS: O(n log n) - ordena por arrival time + O(n) simula = O(n log n).
 *   SJF: O(n²) - por cada unidad de tiempo busca el proceso más corto disponible.
 *   SRTF: O(n·T) - revisa todos los procesos en cada tick de tiempo T.
 *   Round Robin: O(n·T/q) donde q es el quantum. Con quantum pequeño, muchos
 *   cambios de contexto. Priority: O(n²) - similar a SJF pero busca mayor prioridad.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Vector de procesos: almacena n procesos con sus atributos
 *   - Cola ready (Round Robin): hasta n procesos esperando
 *   - Arrays de completion/waiting time: O(n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   O(n) para todos - vector de procesos, colas ready, arrays de tiempos.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateMetrics(vector<Process>& procs) {
    for (auto& p : procs) {
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}

void printResults(const vector<Process>& procs, const string& algorithm) {
    double avgWT = 0;
    for (const auto& p : procs) avgWT += p.waitingTime;
    cout << algorithm << " - Avg WT: " << avgWT / procs.size() << endl;
}






// FCFS - First Come First Serve
void FCFS(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    int currentTime = 0;
    for (auto& p : processes) {
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;
        currentTime += p.burstTime;
        p.completionTime = currentTime;
    }
    
    calculateMetrics(processes);
    printResults(processes, "FCFS");
}

// SJF - Shortest Job First (Non-preemptive)
void SJF(vector<Process> processes) {
    int currentTime = 0;
    int n = processes.size();
    int completed = 0;
    
    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].completionTime == 0 && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            completed++;
        } else {
            currentTime++;
        }
    }
    
    calculateMetrics(processes);
    printResults(processes, "SJF (Non-preemptive)");
}

// SRTF - Shortest Remaining Time First (Preemptive SJF)
void SRTF(vector<Process> processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    while (completed < n) {
        int minIdx = -1;
        int minRemaining = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemaining) {
                    minRemaining = processes[i].remainingTime;
                    minIdx = i;
                }
            }
        }
        
        if (minIdx == -1) {
            currentTime++;
            continue;
        }
        
        processes[minIdx].remainingTime--;
        currentTime++;
        
        if (processes[minIdx].remainingTime == 0) {
            processes[minIdx].completionTime = currentTime;
            completed++;
        }
    }
    
    calculateMetrics(processes);
    printResults(processes, "SRTF (Preemptive)");
}

// Round Robin
void RoundRobin(vector<Process> processes, int quantum) {
    queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<bool> inQueue(n, false);
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }
    
    while (completed < n) {
        if (readyQueue.empty()) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && !inQueue[i] && processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }
        
        int idx = readyQueue.front();
        readyQueue.pop();
        inQueue[idx] = false;
        
        int execTime = min(quantum, processes[idx].remainingTime);
        processes[idx].remainingTime -= execTime;
        currentTime += execTime;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !inQueue[i] && 
                processes[i].remainingTime > 0 && i != idx) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }
        
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            completed++;
        } else {
            readyQueue.push(idx);
            inQueue[idx] = true;
        }
    }
    
    calculateMetrics(processes);
    printResults(processes, "Round Robin (Quantum = " + to_string(quantum) + ")");
}

// Priority Scheduling (Non-preemptive)
void PriorityScheduling(vector<Process> processes) {
    int currentTime = 0;
    int n = processes.size();
    int completed = 0;
    
    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].completionTime == 0 && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            completed++;
        } else {
            currentTime++;
        }
    }
    
    calculateMetrics(processes);
    printResults(processes, "Priority Scheduling");
}

int main() {
    int n;
    cin >> n;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cin >> processes[i].id >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }
    
    FCFS(processes);
    return 0;
}
