from PIL import Image, ImageDraw

def read_coordinates_from_file(file_path):
    coordinates = []
    with open(file_path, 'r') as file:
        for line in file:
            x, y = map(int, line.split())
            coordinates.append((x, y))
    return coordinates

def create_image_and_paint_pixels(coordinates_file):
    # Set the size of the image (adjust as needed)
    image_size = (512, 512)

    # Create a new image with a white background
    image = Image.new("RGB", image_size, "white")

    # Create an ImageDraw object
    draw = ImageDraw.Draw(image)

    # Read coordinates from the file
    black_pixels_coordinates = read_coordinates_from_file(coordinates_file)

    # Set the pixel color to black at the specified coordinates
    for coord in black_pixels_coordinates:
        draw.point(coord, fill="black")

    # Save the modified image
    image.save("output_image.png")

# Example usage
coordinates_file = "black_pixels.txt"  # Update with your file path

create_image_and_paint_pixels(coordinates_file)
