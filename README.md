## miniRT

**miniRT** is a simple ray tracing project implemented in C. It renders 3D scenes featuring spheres with various materials such as Lambertian, Metal, and Dielectric. The project utilizes the **MiniLibX** library for window management and image rendering.


## Features

- **Material support**: Includes Lambertian, Metal, and Dielectric materials for realistic rendering.
- **Anti-aliasing**: Reduces jagged edges by averaging multiple samples per pixel.

## Dependencies

- **MiniLibX**: Required for window management and rendering.

## Reference
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
- [Ray Tracing: The Rest of Your Life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)



## Usage

To compile and run the project:

```sh
make && ./miniRT [aa_sample (optional)]
