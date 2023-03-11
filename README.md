
<h1 align="center">
  <br>
  <a href="./readmeFiles/mainpic.jpg"><img src="./readmeFiles/mainpic.jpg" alt="3Dengine" width="500"></a>
  <br>
  My3DEngine
  <br>
</h1>


<p align="center">
  <a href="#2D LSystems">2D LSystems</a> •
</p>

## 2D LSystems
___

<h1 align="center">
<a href="./readmeFiles/l2d.png"><img src="./readmeFiles/l2d.png" alt="l2d" width="500"></a>
</h1>

<p align="center">
  <a href="#() rule LSystems">() rule LSystems</a> •
  <a href="#Stochaic 2D LSystems">Stochaic 2D LSystems</a>
</p>


## () rule LSystems
___

<h1 align="center">
<a href="./readmeFiles/l2dstack.png"><img src="./readmeFiles/l2dstack.png" alt="l2d" width="500"></a>
</h1>

## Stochaic 2D LSystems
___
  - Put %x behind a rule
    - x is a double with "." as decimal point (always type a decimal point)
  - If you don't use %x, then the percentage of this rule is 100% automatically
  - What if the sum is under 100?
    - The resting percentage get filled with a do not replace rule
      - Eg: Rules: F -> "F+F" %50, G->"F-(F+F)" | Now there is a 50% chance F->"F"
  - What if the sum is above 100?
    - This wil not cause an error internally, it will only result in weird outcomes (the percentages get added in order)
      - Eg: Rules: F -> "F+F" %70, F->"F-F" %50 | The chance for "F-F" is actually 30% not 50%
      - Eg: Rules: F -> "F+F" %10, F->"F-F"   | The chance fo "F-F" is actually 90%
      - Eg: Rules: F-> "F+F", F->"F-F" | The chance for "F-F" is actually 0%







## 3D Lines


## License

MIT

---

> GitHub [@ArneDePeuter](https://github.com/ArneDePeuter) &nbsp;&middot;&nbsp;
> Mail [arne.depeuter@uantwerpen.be]()

