
<h1 align="center">
  <br>
  <a href="./readmeFiles/mainpic.jpg"><img src="./readmeFiles/mainpic.jpg" alt="3Dengine" width="500"></a>
  <br>
  My3DEngine
  <br>
</h1>

<p align="center">
  <a href="#2D-LSystems">2D LSystems</a> •
  <a href="#3D-Lines">3D Lines</a> •
  <a href="#3D-Objects">3D Objects</a>
</p>

## 2D LSystems
___

<h1 align="center">
<a href="./readmeFiles/l2d.png"><img src="./readmeFiles/l2d.png" alt="l2d" width="500"></a>
</h1>

<p align="center">
  <a href="#LSystems-with-brackets">LSystems with brackets</a> •
  <a href="#Stochaic-2D-LSystems">Stochaic 2D LSystems</a>
</p>


### LSystems with brackets
___

<h1 align="center">
<a href="./readmeFiles/l2dstack.png"><img src="./readmeFiles/l2dstack.png" alt="l2d" width="500"></a>
</h1>

### Stochaic 2D LSystems
  - Put %x behind a rule
    - x is a double with "." as decimal point (always type a decimal point)
  - If you don't use %x, then the probability of this rule is automatically 100% 
  - The percentages get added in order
  - What if the sum is under 100:
    - The resting percentage get filled with a "do not replace" rule
      - Eg: Rules: F -> "F+F" %50, G->"F-(F+F)" | Now there is a 50% chance F->"F"
  - What if the sum is above 100:
    - This wil not cause an error internally, it will only result in unexpected outcomes
      - Eg: Rules: F -> "F+F" %70, F->"F-F" %50 | The chance for "F-F" is actually 30% not 50%
      - Eg: Rules: F -> "F+F" %10, F->"F-F"   | The chance fo "F-F" is actually 90%
      - Eg: Rules: F-> "F+F", F->"F-F" %70 | The chance for "F-F" is actually 0% not 70%

<h1 align="center">
<a href="./readmeFiles/stochaic1.png"><img src="./readmeFiles/stochaic1.png" alt="stochaic" width="166" height="166"></a>
<a href="./readmeFiles/stochaic2.png"><img src="./readmeFiles/stochaic2.png" alt="stochaic" width="166" height="166"></a>
<a href="./readmeFiles/stochaic3.png"><img src="./readmeFiles/stochaic3.png" alt="stochaic" width="166" height="166"></a>
</h1>
<h1 align="center">
<a href="./readmeFiles/stochaicrules.png"><img src="./readmeFiles/stochaicrules.png" alt="stochaic" width="500" height="500"></a>
</h1>

## 3D Lines

<h1 align="center">
<a href="./readmeFiles/3dLines.png"><img src="./readmeFiles/3dLines.png" alt="3dl" width="500"></a>
</h1>

## 3D Objects

<h1 align="center">
<a href="./readmeFiles/torus.png"><img src="./readmeFiles/torus.png" alt="torus" width="250" height="250"></a>
<a href="./readmeFiles/bear.png"><img src="./readmeFiles/bear.png" alt="bear" width="250" height="250"></a>
</h1>

- Features:
  - Possibilty to Create a 3D object with a .obj file that is compatible with the parser
  - Z-Buffering (still has inaccuracies)
  - Creating objects:
    -     static Object3D createLineDrawing(const ini::Section &objsec);
    -     static Object3D createTetrahedron();
    -     static Object3D createCube();
    -     static Object3D createIcosahedron();
    -     static Object3D createDodecahedron();
    -     static Object3D createOctahedron();
    -     static Object3D createCylinder(const int &n, const double &h);
    -     static Object3D createCone(const int &n, const double &h);
    -     static Object3D createSphere(const int &n);
    -     static Object3D createTorus(const double &r, const double &R, const int &n, const int &m);
    -     static Object3D loadObj(const std::string &filename);


## License

MIT

---

> GitHub [@ArneDePeuter](https://github.com/ArneDePeuter) &nbsp;&middot;&nbsp;
> Mail [arne.depeuter@uantwerpen.be]()

