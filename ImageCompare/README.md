# WinBitBltImageCompare
Compares two images of the same size / type by using Windows internal BitBlt with SRCINVERT (XOR) ROP.

Windows has a perfectly good (albeit simple) method of comparing two images to see the difference: The venerable BitBlt with ROP SRCINVERT. BitBlt has been in windows since... version 1? It's how bitmaps (including icons, cursors, etc...) get moved onto the screen or printed. There are many modes that BitBlt can work in, as a simple transfer, as a masking operation (AND) where the destination is "cut" by the source, or as an additive process (OR) where the destination is combined with the source... one of those is SRCINVERT where (despite the name) the destination is XORed with the source. XOR means that if the values of the corrisponding pixels are different, the result is a 1 (or white) and if they are the same, the result is 0 (or black). This is useful for before / after comparisons or cases where the images are exactly the same size and type, but one has some (hard for a human to see) difference from the other. The parts that are the same XOR each other out, and the differences stand is stark relief. 

This code is very probably NOT well written as I am 1. Not used to Visual Studio 2. Don't work in C++ on a daily basis but it serves as a proof of concept.

Usage:
ImageCompare.exe image1 image2 output

Where image1 and image2 are bitmap images with exactly the same dimensions, output is a name for the result (format will always be PNG). Minimal error checking for the diminsions matching, and the files loading is included. Again: Proof of concept. 

It also proved to be amazingly difficult to write a simple bloody program, and I hope this might help others who are looking for a sample. Start in Visual Studio with a Win32 Console Application and then change the configuration to x64 (assuming you use a 64 bit OS). The necessary includes are... listed.