# Quantify the brightness of insect cuticle to estimate cuticular melanisation.

### 1) Introduction
The insect cuticle provides both a mechanical and physiochemical barrier against pathogens. The darkness of the cuticle (determined by its level of melanisation and/or sclerotisation) is often positively correlated with the pathogenic resistance of the host. This script automates the quantification of cuticle darkness from previously captured images, calculating the mean brightness of a foreground object (in BGR and HSV colour space) as well as its length and width. Results are outputted to a .text file, and a sample image mask (`mask-FILENAME.png`) is returned for each input.

<img src="https://cloud.githubusercontent.com/assets/17113779/14171680/13bc20c8-f72c-11e5-8445-416986e6260a.jpg" width="400">
<img src="https://cloud.githubusercontent.com/assets/17113779/14171681/13ff3e94-f72c-11e5-8c8f-7f395b562221.jpg" width="400">

**Figure 1**. Sample raw image of a *Tenebrio molitor* elytron (left) and resulting image mask (right). In the mask, pixels composing the mask are displayed in black and the minimum enclosing rectangle is drawn in red.


### 2) Usage
#### a) Compilation
The script requires an installation of the Open Source Computer Vision library, [OpenCV](http://opencv.org/quickstart.html.). The script then needs to be compiled; for example, using the GNU C++ compiler on Linux:

```g ++ -ggdb -o ./cuticleMel ./cuticleMel.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` ```

#### b) Command line use

```./cuticleMel FILE_1 FILE_2 ...```

### 3) Notes
Insect cuticle may be best digitally photographed under direct and intense illumination from a lightbox. For example, the elytra of lighter brown beetles is not readily distinguishable from black beetles under normal lighting conditions (e.g. [Barnes & Siva-Jothy, 2000](http://rspb.royalsocietypublishing.org/content/267/1439/177.short)).
