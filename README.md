Read Me
==========
This repository contains source code for the image processing.
There are 8 image processing function.

----------
Manuals
-------------

This program executes only 256*256 size *bmpfile*.

**Command Format**
 $ ./improc bmpfilename OPTION


  
#### <i class="icon-file"></i> **Option**
 >**Option is  function of image processing.**

				 
         1.  -b : bmp bit plane           
             range of bitplane level [0 ~ 7]
             
         2.  -r : bmp effective resolustion(pixelization)
             range of resolustion level [1 ~ 9]

         3.  -d : bmp dithering             
             dithering filter [D filter, D2 filter, Floyd-steinberg filter] 

         4.  -h : bmp histogram         

         5.  -q : bmp quantization                
             range of quantization level [1 ~ 9]

         6.  -e : bmp edge sharping


#### <i class="icon-file"></i> **Output file**
> **Output file save /app/output.bmp**
                 
                  
     


