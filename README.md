# Program Description

This interactive furniture showroom project was my submission for the final project for the class Informática Gráfica at the University of Jaén. The language is C++ and the main library used is OpenGL.

The program models a showroom that features lights, a table, a floor, and a top-down viewport in the top-right corner.

## Manual

This interactive program contains multiple functionalities that can be used with the keyboard or the mouse.

### Texture and Lighting (Menu)

The user has three options to visualize the scene. The user can choose which scene they wish to visualize using a menu. The menu can be accessed by right-clicking the screen. The three options in the menu are:

| Menu Option | Visualize Scene    |
| :---   | :--- |
| Sin Textura | With Light, No Texture   |
| Con Textura | With Light and Texture   |
| Sin Luz y Textura | Without Light or Texture (Facilitate Object Selection)   |

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/Menu.gif" alt="Menu" width="300" />


### Lighting

The scene has two lights, each of a different type. One is a cone of light and the other a spotlight.

The user can move the spotlight with the keyboard. The position of the spotlight has three parameters: x, y, z.

| Key | Movement    |
| :---   | :--- |
| i/I | Moves the light in the x-axis   |
| j/J | Moves the light in the y-axis   |
| k/K | Moves the light in the z-axis   |

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/Light.gif" alt="Light" width="300" />

### Table (Object)

The scene has a table. The user can move the position of the table and rotate it with the keyboard. The user can also change the color of the top of the table using the mouse.

| Key | Movement    |
| :---   | :--- |
| x/X | Moves the table in the x-axis   |
| z/Z | Moves the table in the z-axis   |
| y/Y | Rotates the table   |

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/MoveTable.gif" alt="Move Table" width="300" />


To change the color of the table, it is necessary to select it. To select it, the user needs to first change the scene to the state "Sin Luz y Textura", using the menu. Then, the user can change the color of the table by clicking and holding the table. With the click maintained, the user can move the mouse to the left or the right to change the color. If the user moves the mouse to the left, the color of the table moves closer to 0 (black). If the user moves the mouse to the right, the color of the table moves closer to 1, or 255 (white).

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/TableSelectionColor.gif" alt="Select Table and Change Color" width="300" />


### Camera

The user can change the view of the camera from parallel to perspective. The user can also zoom in or out.

| Key | Description    |
| :---   | :--- |
| p/P | Changes the camera view from parallel to perspective and vice-versa.   |
| -/+ | Zooms in or out.   |

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/Camera.gif" alt="Camera" width="300" />


### Other Functionalities

The legs of the table are generated using triangle meshes. The user can choose to create the legs using normal vectors. The user can also choose to rotate the entire scene automatically.

| Key | Description    |
| :---   | :--- |
| n/N | Generate the legs (triangle mesh) using normal vectors.   |
| a/A | Automatically rotate the entire scene.  |

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/NormalVectors.gif" alt="Triangle Mesh with Normal Vectors" width="300" />

<img src="https://github.com/hechuno/Interactive-Furniture-Showroom/blob/main/Animations/AutoRotate.gif" alt="Automatic Rotation of the Scene" width="300" />

