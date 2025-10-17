# D3D12 Application Framework

This project is a C++20 application framework for creating Windows desktop applications using Direct3D 12. It provides a modular structure for window management, rendering context setup, and application lifecycle control.

## Features
* Direct3D 12 Rendering Context: Easily initialize and manage D3D12 resources.
* Window Management: Create and control Windows with customizable specifications (title, size, resizability, VSync).
* Application Lifecycle: Simple API for running and stopping the main application loop.
* Triple Buffering: Built-in support for triple buffering via swap chain.
## Structure
* Application: Main entry point and lifecycle manager.
* DXWindow: Handles window creation, message processing, and presentation.
* D3D12Context: Manages Direct3D 12 device and rendering resources.

