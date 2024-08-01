import numpy as np
import cv2

# height and width of image (with colors merged)
width = 1936
height = 1216
num_pixels = width * height
filename = "./frame.bin"

def main():
    with open(filename, 'rb') as file:
        binary_data = file.read()
    
    data_array = np.frombuffer(binary_data, dtype=np.uint8)

    pixel_list = []
    for i, p in enumerate(data_array):
        if i % 4 != 0:
            pixel_list.append(p)
    pixel_array = np.array(pixel_list, dtype=np.uint8)

    image_array = pixel_array[0:].reshape((height, width * 3))

    r = image_array[:, 0::3]
    g = image_array[:, 1::3]
    b = image_array[:, 2::3]
    rgb_image = cv2.merge([b, g, r])

    cv2.imshow('Image', rgb_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
