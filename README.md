
<h1 align="center">
  <br>
  <a href="./readmeFiles/mainpic.jpg"><img src="./readmeFiles/mainpic.jpg" alt="3Dengine" width="500"></a>
  <br>
  My3DEngine
  <br>
</h1>

<div>
  <h3>implemented: </h3>
  <ul>

  <li>
    <a href="#2D-LSystems">2D LSystems</a>
      <ul>
      <li><a href="#Bracket-Rule">Bracket Rule</a></li>
      <li><a href="#Stochaic-Replacement">Stochaic Replacement Rule</a></li>
      </ul>
  </li>

  <li><a href="#3D-Linedrawings">3D Linedrawings</a></li>

  <li>
    <a href="#3D-Objects">3D Objects</a>
    <ul>
      <li><a href="#3D-LSystems">3D LSystems</a></li>
    </ul>
  </li>

  <li>
    <a href="#Zbuffering">ZBuffering</a>
    <ul>
    <li><a href="#ZBuffering-Lines">ZBuffering Lines</a></li>
    <li><a href="#ZBuffering-Triangles">ZBuffering Triangles</a></li>
    </ul>
  </li>

  <li>
    <a href="#3D-Fractals">3D Fractals</a>
    <ul>
    <li><a href="#BuckyBall">BuckyBall</a></li>
    <li><a href="#Mengersponge">Mengersponge</a></li>
    </ul>
  </li>

  <li>
    <a href="#Lighting">Lighting</a>
    <ul>
    <li><a href="#Ambient-Light">Ambient Light</a></li>
    <li><a href="#Diffuse-Light">Diffuse Light</a></li>
    <ul>
    <li><a href="#Infinity-Light">Infinity Light</a></li>
    <li><a href="#Point-Light">Point Light</a></li>
    </ul>
    <li><a href="#Specular-Light">Specular Light</a></li>
    </ul>
  </li>

  <li><a href="#Shadowing">Shadowing</a></li>

  </ul>
</div>

<h1 id="2D-LSystems">2D LSystems</h1>
<hr>

<div align="center">
  <a href="./readmeFiles/l2d.png"><img src="./readmeFiles/l2d.png" alt="l2d" width="500"></a>
</div>

<h1 id="Bracket-Rule">Bracket-Rule</h1>
<hr>

<div align="center">
<a href="./readmeFiles/l2dstack.png"><img src="./readmeFiles/l2dstack.png" alt="l2d" width="500"></a>
</div>

<h1 id="Stochaic-Replacement">Stochaic Replacement Rule</h1>
<hr>

<div align="center">
<a href="./readmeFiles/stochaic1.png"><img src="./readmeFiles/stochaic1.png" alt="stochaic" width="166" height="166"></a>
<a href="./readmeFiles/stochaic2.png"><img src="./readmeFiles/stochaic2.png" alt="stochaic" width="166" height="166"></a>
<a href="./readmeFiles/stochaic3.png"><img src="./readmeFiles/stochaic3.png" alt="stochaic" width="166" height="166"></a>
</div>

<ul>
  <li>Put %x behind a rule
    <ul>
    <li>x is a double with "." as decimal point (always type a decimal point)</li>
    </ul>
  </li>
  <li>If you don't use %x, then the probability of this rule is automatically 100%</li>
  <li>The percentages get added in order</li>
  <li>
    What if the sum is under 100:
    <ul>
    <li>The resting percentage get filled with a "do not replace" rule</li>
    <li>Eg: Rules: F -> "F+F" %50, G->"F-(F+F)" | Now there is a 50% chance F->"F"</li>
    </ul>
  </li>
  <li>
    What if the sum is above 100:
    <ul>
    <li>This wil not cause an error, it will only result in unexpected outcomes</li>
    <li>Eg: Rules: F -> "F+F" %70, F->"F-F" %50 | The chance for "F-F" is actually 30% not 50%</li>
    <li>Eg: Rules: F -> "F+F" %10, F->"F-F"   | The chance fo "F-F" is actually 90%</li>
    <li>Eg: Rules: F-> "F+F", F->"F-F" %70 | The chance for "F-F" is actually 0% not 70%</li>
    </ul>
  </li>
</ul>

<div align="center">
<a href="./readmeFiles/stochaicrules.png"><img src="./readmeFiles/stochaicrules.png" alt="stochaic" width="500" height="500"></a>
</div>

<h1 id="3D-Linedrawings">3D Linedrawings</h1>
<hr>

<div align="center">
<a href="./readmeFiles/3dLines.png"><img src="./readmeFiles/3dLines.png" alt="3dl" width="500"></a>
</div>

<h1 id="3D-Objects">3D Objects</h1>
<hr>

<div align="center">
<a href="./readmeFiles/torus.png"><img src="./readmeFiles/torus.png" alt="torus" width="250" height="250"></a>
<a href="./readmeFiles/bear.png"><img src="./readmeFiles/bear.png" alt="bear" width="250" height="250"></a>
</div>

<h3>Implemented Objects:</h3>
<ul>
  <li><b>Object3D::Object3DFactory::createLineDrawing(const ini::Section &objsec);</b></li>
  <li><b>Object3D::Object3DFactory::createTetrahedron();</b></li>
  <li><b>Object3D::Object3DFactory::createCube();</b></li>
  <li><b>Object3D::Object3DFactory::createIcosahedron();</b></li>
  <li><b>Object3D::Object3DFactory::createDodecahedron();</b></li>
  <li><b>Object3D::Object3DFactory::createOctahedron();</b></li>
  <li><b>Object3D::Object3DFactory::createCylinder(const int &n, const double &h);</b></li>
  <li><b>Object3D::Object3DFactory::createCone(const int &n, const double &h);</b></li>
  <li><b>Object3D::Object3DFactory::createSphere(const int &n);</b></li>
  <li><b>Object3D::Object3DFactory::createTorus(const double &r, const double &R, const int &n, const int &m);</b></li>
  <li><b>Object3D::Object3DFactory::loadObj(const std::string &filename);</b></li>
  <ul>
  <li>Loads in an object from any .obj file compatible with the obj Parser <b>(examples provided in exampleFiles Folder)</b></li>
  </ul>
</ul> 

<h1 id="3D-LSystems">3D LSystems</h1>
<hr>

<div align="center">
<a href="./readmeFiles/3dLsys.png"><img src="./readmeFiles/3dLsys.png" alt="lsys" width="500" height="500"></a>
</div>

<h1 id="Zbuffering">Zbuffering</h1>
<hr>

<h1 id="ZBuffering-Lines">ZBuffering Lines</h1>
<hr>

<div align="center">
<a href="./readmeFiles/zbufWf.png"><img src="./readmeFiles/zbufWf.png" alt="zbWf" width="500" height="500"></a>
</div>

<h1 id="ZBuffering-Triangles">ZBuffering Triangles</h1>
<hr>

<div align="center">
<a href="./readmeFiles/zbufTriag.png"><img src="./readmeFiles/zbufTriag.png" alt="zbTg" width="500" height="500"></a>
</div>

<h1 id="3D-Fractals">3D Fractals</h1>
<hr>

<div align="center">
<a href="./readmeFiles/fractal3d.png"><img src="./readmeFiles/fractal3d.png" alt="f3d" width="250" height="250"></a>
<a href="./readmeFiles/fractal3d2.png"><img src="./readmeFiles/fractal3d2.png" alt="f3d2" width="250" height="250"></a>
</div>

<h3>Implemented Fractal Objects:</h3>
<ul>
  <li><b>Object3D::Object3DFactory::createFractalCube(const double &fractalScale, const int &nrIterations);</b></li>
  <li><b>Object3D::Object3DFactory::createFractalDodecahedron(const double &fractalScale, const int &nrIterations);</b></li>
  <li><b>Object3D::Object3DFactory::createFractalIcosahedron(const double &fractalScale, const int &nrIterations);</b></li>
  <li><b>Object3D::Object3DFactory::createFractalOctahedron(const double &fractalScale, const int &nrIterations);</b></li>
  <li><b>Object3D::Object3DFactory::createFractalTetrahedron(const double &fractalScale, const int &nrIterations);</b></li>
</ul>

<h1 id="BuckyBall">BuckyBall</h1>
<hr>

<div align="center">
<a href="./readmeFiles/buckyball.png"><img src="./readmeFiles/buckyball.png" alt="bucky" width="250" height="250"></a>
<a href="./readmeFiles/buckyFrac.png"><img src="./readmeFiles/buckyFrac.png" alt="buckyfrac" width="250" height="250"></a>
</div>

<ul>
    <li><b>Object3D::Object3DFactory::createBuckyBall();</b></li>
    <li><b>Object3D::Object3DFactory::createFractalBuckyBall(const double &fractalScale, const int &nrIterations);</b></li>
</ul>

<h1 id="Mengersponge">Mengersponge</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/menger.png"><img src="./readmeFiles/menger.png" alt="meng" width="500" height="500"></a>
</div>

<ul>
    <li><b>Object3D::Object3DFactory::createMenger(const int &nrIterations);</b></li>
</ul>

<h1 id="Lighting">Lighting</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/light1.png"><img src="./readmeFiles/light1.png" alt="light1" width="500" height="500"></a>
</div>

<h1 id="Ambient-Light">Ambient Light</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/ambient.png"><img src="./readmeFiles/ambient.png" alt="ambient" width="400" height="500"></a>
</div>

<h1 id="Diffuse-Light">Diffuse Light</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/diffuse.png"><img src="./readmeFiles/diffuse.png" alt="diffuse" width="500" height="500"></a>
</div>

<h1 id="Infinity-Light">Infinity Light</h1>
<p>This light only has a pointing direction.</p>
<hr>


<div align="center">
    <a href="./readmeFiles/infl.png"><img src="./readmeFiles/infl.png" alt="infl" width="500" height="500"></a>
</div>

<h1 id="Point-Light">Point Light</h1>
<p>This light onlyl has a location.</p>
<p>It could be a spotlight, if the spotangle != -1.</p>
<hr>

<div align="center">
    <a href="./readmeFiles/pointL.png"><img src="./readmeFiles/pointL.png" alt="pointL" width="400" height="500"></a>
</div>

<h3>SpotLight</h3>
<div align="center">
    <a href="./readmeFiles/spotl.png"><img src="./readmeFiles/spotl.png" alt="spotl" width="400" height="500"></a>
</div>

<h1 id="Specular-Light">Specular Light</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/spec1.png"><img src="./readmeFiles/spec1.png" alt="spec1" width="250" height="250"></a>
    <a href="./readmeFiles/spec2.png"><img src="./readmeFiles/spec2.png" alt="spec2" width="250" height="250"></a>
</div>

<h1 id="Shadowing">Shadowing</h1>
<hr>

<div align="center">
    <a href="./readmeFiles/shadow1.png"><img src="./readmeFiles/shadow1.png" alt="shadow1" width="250" height="250"></a>
    <a href="./readmeFiles/shadow2.png"><img src="./readmeFiles/shadow2.png" alt="shadow2" width="250" height="250"></a>
</div>

## License
MIT

---

> GitHub [@ArneDePeuter](https://github.com/ArneDePeuter) &nbsp;&middot;&nbsp;
> Mail [arne.depeuter@uantwerpen.be]()

