# PMF Analysis of Grayscale Image

This C program reads a BMP image file, calculates its histogram, mean, variance, standard deviation, probability mass function (PMF), and normal distribution. It then writes the results to corresponding text files.

The program is useful for analyzing the statistical properties of an image and also provides an example of understanding the BMP header structure.

## Table of Contents

- [How to Use](#how-to-use)
- [BMP Header Structure](#bmp-header-structure)
- [Statistics and Results](#statistics-and-results)

## How to Use

### Prerequisites
- Before running the program, make sure you have a grayscale BMP image named `test.bmp` in the same directory as the program.

   Clone the repository:

    ```bash
    git clone https://github.com/unsulliedd/C-PMF-Analysis-of-Grayscale-Image.git
    ```

## Output

- Check the generated text files for results:
    - `histogram.txt`
    - `pmf.txt`
    - `normal.txt`

## BMP Header Structure

- **bfType:** BM (BMP file type)
- **bfSize:** File size
- **bfOffBits:** Offset of pixel data
- **Width:** Horizontal pixels
- **Height:** Vertical pixels
- **Bits per Pixel:** Bits per pixel
- **X/Y Pixels per Meter:** Resolution
- **Colors Used/Important:** Color information

## Statistics and Results

- **Mean:** Mean pixel intensity
- **Variance:** Variance of pixel intensities
- **Standard Deviation:** Standard deviation of pixel intensities
- **Total Pixel:** Total number of pixels in the image

  
