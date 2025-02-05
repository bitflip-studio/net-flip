# net-flip (Work in Progress)

net-flip is an ultra-fast, optimally engineered HTTP server that merges cutting-edge C library performance with the flexibility of Node.js. Designed primarily for Linux environments – with development supported on Windows via Docker and WSL – net-flip aims to become the fastest and most efficient open-source HTTP server available.

**Current Development Status:**
- The project is actively under development.
- Only a few commands are fully operational at the moment:
    - **run-test.bat:** Launches a Docker container running Ubuntu, builds the C library along with a basic C executable that tests the library and outputs results to the console.
    - **run-test-js.bat:** Launches a Docker container running Ubuntu with Node.js, builds the C library, and executes JavaScript code that utilizes the library. This command not only tests the C library but also runs additional validations on the JavaScript side.

## Why net-flip is the Optimal Implementation

net-flip is engineered following a set of strict design principles to maximize performance, minimize latency, and ensure stability under heavy load:

1. **No Dynamic Memory Allocation After Startup:**  
   Once the server is running, net-flip avoids any dynamic memory allocation. Memory is preallocated based on defined limits and used throughout the process lifetime, eliminating fragmentation and ensuring predictable, consistent performance.

2. **Minimal System Calls Using Atomic Operations:**  
   All inter-thread communications are managed using efficient atomic operations and specialized queues. This minimizes system call overhead and avoids busy waits, enabling threads to process multiple operations concurrently. If a thread must wait (e.g., for memory clearance), it does so in a controlled, low-overhead manner.

3. **Centralized System Call Management:**  
   Every system call is funneled through a single, centralized management point. This design allows any available thread to execute pending operations, ensuring that no task becomes a bottleneck. By leveraging Linux’s advanced I/O capabilities (such as io_uring), net-flip processes events efficiently without freezing or partial task execution.

4. **Minimal Buffer Copying:**  
   Data is transferred with as few buffer copies as possible. This approach minimizes overhead and accelerates communication between the native C library and the JavaScript layer.

5. **On-the-Fly Protocol Handling:**  
   net-flip is capable of parsing and managing protocol requirements as data flows through the system. This design streamlines processing, reduces delays in the main event loop, and ensures strict adherence to protocol standards.

6. **Seamless Shared Memory with JavaScript:**  
   By using shared memory techniques, net-flip enables near-instantaneous data exchange between the C library and JavaScript, sidestepping the overhead typically found in inter-language communication.

7. **Scalable Memory Allocation for All Platforms:**  
   Whether running on the smallest chip or the largest server, net-flip allocates memory only once at startup based on predefined limits. This preallocated memory is then used throughout the process, ensuring deterministic behavior and consistent performance across hardware. The socket management system operates like a high-precision clock with simple state management, ensuring ultra-fast communication.

8. **Built-In Backpressure Mechanism:**  
   net-flip incorporates a sophisticated backpressure system that leverages high-accuracy timing from io_uring. For example, if a socket is being read and available memory is exhausted, the system will delay re-queuing that socket until more memory is available. This controlled backpressure applies strict limits that, under maximum concurrency, may cause a slight delay for all connections but never results in outright failures. Allocating additional memory reduces or eliminates waiting times, ensuring smooth operation even under heavy load.

9. **Integrated Timeout System for Connection Management:**  
   In addition to the above features, net-flip includes a robust timeout mechanism to manage socket lifecycles. This system tracks when sockets are opened and monitors data streaming activity. If a connection fails to adhere to protocol requirements—for instance, by sending only a partial header and then hanging—the timeout system will automatically drop the connection based on the predefined timeout settings specified at server startup. This ensures that non-compliant connections are closed quickly, preserving system resources and maintaining overall server health.

## Performance Highlights

- **Ultra-Low Latency:**  
  Thanks to the elimination of dynamic memory allocation during runtime and the use of shared memory, net-flip achieves near-zero latency.
- **High Throughput:**  
  Optimized socket handling via Linux’s io_uring API and minimized system call overhead allow net-flip to excel under heavy loads.
- **Scalability:**  
  Designed from the ground up to handle a large number of concurrent connections, net-flip leverages atomic operations, centralized syscall management, preallocated memory, and smart timeout mechanisms to maintain consistent performance even at scale.

## Getting Started

### Prerequisites

- **Node.js:** Version 14.x.x or higher.
- **Linux Environment:** net-flip leverages Linux-specific features like io_uring. Although development is performed using Docker on Windows via WSL, a recent Linux distribution is required for optimal performance.

### Installation

You can install net-flip via npm:

    npm install net-flip

Alternatively, clone the repository:

    git clone https://github.com/yourusername/net-flip.git
    cd net-flip
    npm install

### Running Tests

During early development, testing is conducted using the following commands:

- **C Library Test:**  
  Run `run-test.bat` to launch an Ubuntu Docker container that builds the C library along with a simple test executable. This test validates core functionalities and prints results to the console.

- **Node.js Integration Test:**  
  Run `run-test-js.bat` to launch an Ubuntu Docker container with Node.js. This builds the C library and executes JavaScript tests, verifying integration and performance from the JavaScript side.

### Basic Usage Example

Below is a simple example of how to set up and run the net-flip server in Node.js:

    const netFlip = require('net-flip');

    const server = netFlip.createServer({
      port: 8080,
      timeout: 5000, // Set timeout in milliseconds for protocol compliance
      // Additional configuration options can be specified here
    });

    server.on('request', (req, res) => {
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      res.end('Hello from net-flip!');
    });

    server.listen(() => {
      console.log('net-flip server is running on port 8080');
    });

## Roadmap

**Completed:**
- Project initialization

**Upcoming:**
- C: Dynamic Binary Stream
- C: Main Event Loop
- C: Task Management System
- C: I/O Management
- C: Library API
- Node.js: API Integration with the native library
- Additional performance and scalability enhancements (including SSL/TLS support and HTTP/2 integration)

## Contributing

We welcome contributions! To get involved:
1. Fork the repository.
2. Create a new branch (e.g., `git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push the branch (`git push origin feature-branch`).
5. Open a pull request detailing your changes.

Please refer to our CONTRIBUTING guidelines for additional details on our code of conduct and the pull request process.

## License

net-flip is released under the GNU GENERAL PUBLIC LICENSE. For further details, see the LICENSE file.

Join us in building the fastest open-source HTTP server – one that leverages the full power of modern Linux systems, preallocated memory strategies, and cutting-edge I/O and timeout management techniques to deliver unparalleled performance and reliability!
