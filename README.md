# Algorithm Project Final
* * *
### 프로젝트 목표
* **0-1 KnapSack Problem** Solving  
  * **Dynamic Programming**  
  * **Genetic Algorithm**  
### 사용 Tool
- [x] Visual Studio  
### 프로젝트 결과 (간략)
> **NP** 중에서도 대표 주자인 **NP-Complete**
> **NP-Complete** 중에서도 유명한 **0-1 KnapSack**을 다양한 방식으로 접근
> > **GA**를 이용할 경우 다음과 같은 **기법**들을 고려하며 구현
> > > **Encoding**  
> > > **Selection**  
> > > **Crossover**  
> > > **Mutation**  

<img src="/image/d1.png" width="700px" height="250px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d2.png" width="420px" height="300px" alt="BlockDiagram"></img><br/>
<img src="/image/d3.png" width="420px" height="350px" alt="BlockDiagram"></img><br/>
> **KnapSack Problem DP vs GA** 서로 비교 및 분석한 결과  
> > **DP < GA 👉 GA < DP**  
> > 데이터 셋이 작을 때에는 DP가 빠르지만, 데이터 셋이 많아질수록 GA가 성능이 좋음  
> > > 사용한 **GA**기법  
> > > **Binary Encoding, Roulette Selection, MultiPoint Crossover, Insertion Mutation**  

<img src="/image/d4.png" width="700px" height="250px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d5.png" width="420px" height="280px" alt="BlockDiagram"></img><br/>
> **KnapSack Problem GA (RS) vs GA (TS)** 서로 비교 및 분석한 결과  
> > **GA (RS) < GA (TS)**  
> > **Roulette Selection**기법이 **Tournament Selection**기법보다 KnapSack Problem에 효율적임을 확인  
> > > 사용한 **GA**기법  
> > > **Binary Encoding, Roulette & Tournament Selection, MultiPoint Crossover, Insertion Mutation**  

<img src="/image/d6.png" width="700px" height="250px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d7.png" width="420px" height="280px" alt="BlockDiagram"></img><br/>
> **KnapSack Problem GA (TC) vs GA (SC)** 서로 비교 및 분석한 결과  
> > **GA (TC) < GA (SC)**  
> > **TwoPoint Crossover**이 **SinglePoint Crossover**기법보다 KnapSack Problem에 효율적임을 확인  
> > > 사용한 **GA**기법  
> > > **Binary Encoding, Roulette Selection, SinglePoint & MultiPoint Crossover, Insertion Mutation**  

<img src="/image/d8.png" width="700px" height="250px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d9.png" width="420px" height="280px" alt="BlockDiagram"></img><br/>
> **KnapSack Problem GA (IM) vs GA (IVM)** 서로 비교 및 분석한 결과  
> > **GA (IM) < GA (IVM)**  
> > **Insertion Mutation**이 **Inversion Mutation**보다 KnapSack Problem에 효율적임을 확인  
> > > 사용한 **GA**기법  
> > > **Binary Encoding, Roulette Selection, MultiPoint Crossover, Insertion & Inversion Mutation**
