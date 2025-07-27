# UIU Permanent Campus 3D Visualization

A comprehensive 3D visualization of the United International University (UIU) Permanent Campus built using OpenGL and GLUT. This project renders a detailed virtual campus environment with buildings, roads, natural elements, and interactive camera controls.

## 🎯 Features

### 🏗️ Campus Architecture
- **Multi-story Buildings**: Detailed building structures with textured walls, rooftops, and balconies
- **Central Plaza**: Main campus area with connecting walkways
- **Canteen Facilities**: Multiple dining areas throughout the campus
- **Swimming Pool**: Recreational facility with water textures

### 🌿 Natural Environment
- **Lake System**: Multiple water bodies with realistic water textures
- **Trees**: Procedurally generated trees with trunk and foliage
- **Grass Areas**: Textured green spaces and lawns
- **Sky Dome**: 360-degree textured sky environment

### 🛣️ Infrastructure
- **Road Network**: Interconnected road system with proper texturing
- **Staircases**: Multi-level access with realistic step generation
- **Walkways**: Campus pathways connecting different areas
- **Umbrellas**: Decorative outdoor furniture elements

### 🎮 Interactive Controls
- **360° Camera Movement**: Full rotational camera control
- **Height Adjustment**: Vertical camera positioning
- **Zoom Functionality**: Dynamic distance control
- **Real-time Navigation**: Smooth camera transitions

## 🔧 Technical Specifications

### Dependencies
- **OpenGL**: Core graphics rendering
- **GLUT**: Window management and input handling
- **Windows.h**: Windows-specific functionality
- **Standard C Libraries**: Math, stdio, stdlib

### Rendering Features
- **Texture Mapping**: BMP image loading and application
- **3D Transformations**: Translation, rotation, and scaling
- **Depth Testing**: Proper 3D object layering
- **Double Buffering**: Smooth animation rendering
- **Quadric Objects**: Spheres and cylinders for organic shapes

## 📁 Project Structure

```
Graphics Project/
├── Graphics Project.cpp    # Main source code
├── image/                 # Texture assets
│   ├── grass.bmp         # Grass texture
│   ├── road.bmp          # Road surface texture
│   ├── wall.bmp          # Building wall texture
│   ├── sky.bmp           # Sky dome texture
│   ├── lake.bmp          # Water surface texture
│   ├── field.bmp         # Field texture
│   ├── extend1.bmp       # Building extension texture
│   ├── extend2.bmp       # Additional building texture
│   └── 6.bmp             # Additional texture asset
└── README.md             # Project documentation
```

## 🚀 Getting Started

### Prerequisites
- Windows Operating System
- Visual Studio or compatible C++ compiler
- OpenGL development libraries
- GLUT library installed

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/uiu-campus-3d.git
   cd uiu-campus-3d
   ```

2. **Set up development environment**
   - Install OpenGL development libraries
   - Configure GLUT library paths
   - Ensure all texture files are in the `image/` directory

3. **Compile the project**
   ```bash
   # Using Visual Studio
   # Open project in Visual Studio and build
   
   # Using command line (adjust paths as needed)
   gcc -o campus Graphics\ Project.cpp -lopengl32 -lglu32 -lglut32
   ```

4. **Run the application**
   ```bash
   ./campus.exe
   ```

## 🎮 Controls

### Camera Navigation
- **Arrow Keys**:
  - `↑/↓`: Adjust camera height
  - `←/→`: Rotate camera around campus
- **Zoom**:
  - `+`: Zoom in
  - `-`: Zoom out
- **Additional Controls**:
  - `Q/E`: Pitch control
  - `L/R`: Left/Right movement
  - `HOME`: Reset camera position

### Debug Controls
- `X/Y/Z`: Adjust object positions (development mode)

## 🏛️ Campus Layout

The virtual campus includes several key areas:

1. **Academic Buildings**: Multi-story structures with detailed architecture
2. **Central Courtyard**: Open space with landscaping
3. **Recreation Area**: Swimming pool and surrounding facilities
4. **Dining Facilities**: Multiple canteen locations
5. **Natural Areas**: Lake system and green spaces
6. **Transportation**: Road network and pedestrian pathways

## 🎨 Texture System

The project uses a comprehensive texture mapping system:
- **Bitmap Loading**: Custom BMP file loader
- **Texture Binding**: OpenGL texture management
- **UV Mapping**: Proper texture coordinate mapping
- **Mipmapping**: Automatic mipmap generation for quality

## 🔄 Rendering Pipeline

1. **Initialization**: OpenGL context setup and texture loading
2. **Camera Setup**: View matrix configuration
3. **Scene Rendering**: 
   - Background (sky dome)
   - Terrain and water bodies
   - Buildings and structures
   - Natural elements (trees, grass)
   - Infrastructure (roads, stairs)
4. **Buffer Swap**: Double buffer presentation

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Contribution Guidelines
- Follow existing code style and conventions
- Add comments for complex rendering logic
- Test thoroughly on Windows environment
- Update documentation for new features

## 📝 Code Structure

### Main Components

- **Texture Management**: `loadBitmapImage()`, `loadAllImages()`
- **Building Rendering**: `building()`, `plane()`, `canteen()`
- **Natural Elements**: `trees()`, `lake()`, `umbrella()`
- **Infrastructure**: `road()`, `stairs()`, `stair_back()`
- **Camera System**: `specialKeyListener()`, `keyboardListener()`
- **Main Loop**: `display()`, `animate()`, `main()`

## 🐛 Known Issues

- Texture loading requires specific BMP format
- Windows-specific dependencies limit cross-platform compatibility
- Some rendering artifacts may occur with extreme camera angles

## 📋 Future Enhancements

- [ ] Cross-platform compatibility (Linux/macOS)
- [ ] Additional texture formats support
- [ ] Enhanced lighting system
- [ ] Weather effects (rain, fog)
- [ ] Animated elements (moving water, swaying trees)
- [ ] Sound integration
- [ ] VR compatibility

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



## 🙏 Acknowledgments

- United International University for campus reference
- OpenGL community for documentation and examples
- GLUT library developers for windowing system
- Contributors to texture assets and resources


## 🔗 Related Projects

- [OpenGL Tutorial Series](https://learnopengl.com/)
- [GLUT Documentation](https://www.opengl.org/resources/libraries/glut/)
- [3D Graphics Programming Resources](https://www.khronos.org/opengl/)

---

*Built with ❤️ using OpenGL and GLUT*
