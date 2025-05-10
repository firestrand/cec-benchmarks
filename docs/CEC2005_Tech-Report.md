# Problem Definitions and Evaluation Criteria for the CEC 2005

# Special Session on Real-Parameter Optimization

P. N. Suganthan¹, N. Hansen², J. J. Liang¹, K. Deb³, Y. -P. Chen⁴, A. Auger², S. Tiwari³

¹School of EEE, Nanyang Technological University, Singapore, 639798

²(ETH) Zürich, Switzerland

³Kanpur Genetic Algorithms Laboratory (KanGAL), Indian Institute of Technology, Kanpur, PIN 208 016, India

⁴Natural Computing Laboratory, Department of Computer Science, National Chiao Tung University, Taiwan

epnsugan@ntu.edu.sg, Nikolaus.Hansen@inf.ethz.ch, liangjing@pmail.ntu.edu.sg, deb@iitk.ac.in, ypchen@csie.nctu.edu.tw, Anne.Auger@inf.ethz.ch, tiwaris@iitk.ac.in

Technical Report, Nanyang Technological University, Singapore

And

KanGAL Report Number 2005005 (Kanpur Genetic Algorithms Laboratory, IIT Kanpur)

May 2005

# Acknowledgement

We also acknowledge the contributions by Drs / Professors Maurice Clerc (Maurice.Clerc@WriteMe.com), Bogdan Filipic (bogdan.filipic@ijs.si), William Hart (wehart@sandia.gov), Marc Schoenauer (Marc.Schoenauer@lri.fr), Hans‑Paul Schwefel (hans‑paul.schwefel@cs.uni‑dortmund.de), Aristin Pedro Ballester (p.ballester@imperial.ac.uk) and Darrell Whitley (whitley@CS.ColoState.EDU).
---
# Problem Definitions and Evaluation Criteria for the CEC 2005

# Special Session on Real-Parameter Optimization

In the past two decades, different kinds of optimization algorithms have been designed and applied to solve real‑parameter function optimization problems. Some of the popular approaches are real‑parameter EAs, evolution strategies (ES), differential evolution (DE), particle swarm optimization (PSO), evolutionary programming (EP), classical methods such as quasi‑Newton method (QN), hybrid evolutionary‑classical methods, other non‑evolutionary methods such as simulated annealing (SA), tabu search (TS) and others. Under each category, there exist many different methods varying in their operators and working principles, such as correlated ES and CMA‑ES. In most such studies, a subset of the standard test problems (Sphere, Schwefel's, Rosenbrock's, Rastrigin's, etc.) is considered. Although some comparisons are made in some research studies, often they are confusing and limited to the test problems used in the study. In some occasions, the test problem and chosen algorithm are complementary to each other and the same algorithm may not work in other problems that well. There is definitely a need of evaluating these methods in a more systematic manner by specifying a common termination criterion, size of problems, initialization scheme, linkages/rotation, etc. There is also a need to perform a scalability study demonstrating how the running time/evaluations increase with an increase in the problem size. We would also like to include some real world problems in our standard test suite with codes/executables.

In this report, 25 benchmark functions are given and experiments are conducted on some real‑parameter optimization algorithms. The codes in Matlab, C and Java for them could be found at http://www.ntu.edu.sg/home/EPNSugan/. The mathematical formulas and properties of these functions are described in Section 2. In Section 3, the evaluation criteria are given. Some notes are given in Section 4.

# 1. Summary of the 25 CEC’05 Test Functions

# Unimodal Functions (5):

- F₁: Shifted Sphere Function
- F₂: Shifted Schwefel’s Problem 1.2
- F₃: Shifted Rotated High Conditioned Elliptic Function
- F₄: Shifted Schwefel’s Problem 1.2 with Noise in Fitness
- F₅: Schwefel’s Problem 2.6 with Global Optimum on Bounds

# Multimodal Functions (20):

# Basic Functions (7):

- F₆: Shifted Rosenbrock’s Function
- F₇: Shifted Rotated Griewank’s Function without Bounds
- F₈: Shifted Rotated Ackley’s Function with Global Optimum on Bounds
- F₉: Shifted Rastrigin’s Function
- F₁₀: Shifted Rotated Rastrigin’s Function
- F₁₁: Shifted Rotated Weierstrass Function
- F₁₂: Schwefel’s Problem 2.13

# Expanded Functions (2):
---
# Hybrid Composition Functions (11):

- F₁₅: Hybrid Composition Function
- F₁₆: Rotated Hybrid Composition Function
- F₁₇: Rotated Hybrid Composition Function with Noise in Fitness
- F₁₈: Rotated Hybrid Composition Function
- F₁₉: Rotated Hybrid Composition Function with a Narrow Basin for the Global Optimum
- F₂₀: Rotated Hybrid Composition Function with the Global Optimum on the Bounds
- F₂₁: Rotated Hybrid Composition Function
- F₂₂: Rotated Hybrid Composition Function with High Condition Number Matrix
- F₂₃: Non‑Continuous Rotated Hybrid Composition Function
- F₂₄: Rotated Hybrid Composition Function
- F₂₅: Rotated Hybrid Composition Function without Bounds

# Pseudo-Real Problems:

Available from http://www.cs.colostate.edu/~genitor/functions.html. If you have any queries on these problems, please contact Professor Darrell Whitley. Email: whitley@CS.ColoState.EDU
---
# 2. Definitions of the 25 CEC’05 Test Functions

# 2.1 Unimodal Functions:

# 2.1.1. F1: Shifted Sphere Function

F1(x) = &sum;i=1D zi2 + fbias₁, z = x - o, x = [x1, x2,..., xD]

D: dimensions. o = [o1, o2,..., oD] : the shifted global optimum.

# Properties:

- Unimodal
- Shifted
- Separable
- Scalable

x ∈ [100, 100], Global optimum: x* = o1, F(x*) = fbias₁ = -450

# Associated Data files:

|Name:|sphere_func_data.mat|
|---|---|
| |sphere_func_data.txt|
|Variable:|o|
| |1*100 vector - the shifted global optimum|
|When cut using:|o = o(1:D)|
|Name:|fbias_data.mat|
| |fbias_data.txt|
|Variable:|f_bias|
| |1*25 vector, record all the 25 function’s fbiasi|

---
# 2.1.2. F2: Shifted Schwefel’s Problem 1.2

F(x) = ∑i=1D ∑j=1D (zj)² + fbias

z = x - o

x = [x1, x2,..., xD]

D: dimensions

o = [o1, o2,...,oD] : the shifted global optimum

Properties:

- Unimodal
- Shifted
- Non-separable
- Scalable

x ∈ [100,100], Global optimum x = o, F(x) = fbias = -450

# Associated Data files:

|Name:|schwefel_102_data.mat|
|---|---|
| |schwefel_102_data.txt|
|Variable:|o 1*100 vector the shifted global optimum|

When cut using, o = o(1:D)
---
2.1.3. F₃: Shifted Rotated High Conditioned Elliptic Function
        D       i−1
F ( )   ∑(10 )     z    f _ bias ,  z = (x − o)*M , x = [x , x ,..., x  ]
  3 x =       6 D−1  2 +
                     i         3                       1  2     D
       i=1
D: dimensions
       o =[o₁, o₂,...,oD ]  : the shifted global optimum
M: orthogonal matrix
                                                                      100
                              Figure 2-3    100 100
                                         3‑D map for 2‑D function
Properties:
    ¾  Unimodal
    ¾  Shifted
    ¾  Rotated
    ¾  Non‑separable
    ¾  Scalable
        x ∈ −                             x  = o  F (x ) = f_bias =‑ 450
    ¾      [ 100,100]ᴰ , Global optimum     *    , 3  *          3
Associated Data files:
Name:          high_cond_elliptic_rot_data.mat
               high_cond_elliptic_rot_data.txt
Variable:      o      1*100 vector           the shifted global optimum
  When
 cut
 using,                         o=o(1:D)
Name:         elliptic_M_D10 .mat            elliptic_M_D10 .txt
Variable:      M 10*10
                     matrix
Name:         elliptic_M_D30 .mat            elliptic_M_D30 .txt
Variable:      M 30*30
                     matrix
Name:         elliptic_M_D50 .mat            elliptic_M_D50 .txt
Variable:      M 50*50
                     matrix

                                                6
---
# 2.1.4. F₄: Shifted Schwefel’s Problem 1.2 with Noise in Fitness

F (x) = (∑ ∑ (z) ) * (1 + 0.4 N(0,1)) + f_bias

z = x - o

D: dimensions

o = [o₁, o₂,...,oD]: the shifted global optimum

# Properties:

- Unimodal
- Shifted
- Non-separable
- Scalable
- Noise in fitness

x ∈ [-100, 100]ᴰ, Global optimum F₄(x*) = f_bias₄ = -450

# Associated Data file:

|Name:|schwefel_102_data.mat|
|---|---|
| |schwefel_102_data.txt|
|Variable:|o 1*100 vector the shifted global optimum|
| |When using, cut o = o(1:D)|

---
# 2.1.5. F₅: Schwefel’s Problem 2.6 with Global Optimum on Bounds

f ( ) , x = [1,3], f (x ) = 0

x = max{ x₁ + 2x₂ −7 , 2x₁ + x₂ −5}, i = 1,...,n

Extend to D dimensions:

F ( ) , x = [x₁, x₂,..., xₖ]

x₅ = max{ A x − B } + f_bias, i = 1,..., D

D: dimensions

A is a D*D matrix, aij are integer random numbers in the range [‑500, 500], det(A) ≠ 0, Ai is the iᵗʰ row of A.

Bi = Ai * o, o is a D*1 vector, oi are random numbers in the range [‑100,100]

After load the data file, set o = −100, for i = 1, 2,..., D / 4, o = 100, for i = ⎢3D / 4 ,..., D

i ⎢ 100 ⎥ i ⎦

⎣ 200

100

100 200 200 100

# Figure 2-5 3‑D map for 2‑D function

# Properties:

- ¾ Unimodal
- ¾ Non‑separable
- ¾ Scalable
- ¾ If the initialization procedure initializes the population at the bounds, this problem will be solved easily.
- x ∈ [−100,100]ᴰ, Global optimum x* = o, F₅ (x*) = f_bias₅ = ‑310

# Associated Data file:

|Name:|schwefel_206_data.mat|
|---|---|
| |schwefel_206_data.txt|
|Variable:|o 1*100 vector the shifted global optimum|
| |A 100*100 matrix|

When cut using, o = o(1:D) A = A(1:D,1:D)

In schwefel_206_data.txt, the first line is o (1*100 vector), and line 2‑line 101 is A (100*100 matrix)
---
# 2.2 Basic Multimodal Functions

# 2.2.1. F₆: Shifted Rosenbrock’s Function

Fx(x) = &sum;i=1D-1 (100(z2 - zi2)2 + (zi - 1)2) + fbias, z = x - o + 1, x = [x1, x2, ..., xD]

D: dimensions

o = [o1, o2, ..., oD]: the shifted global optimum

Properties:

- Multi-modal
- Shifted
- Non-separable
- Scalable
- Having a very narrow valley from local optimum to global optimum

x ∈ [-100, 100]D

Global optimum, F6(x*) = fbias₆ = 390

# Associated Data file:

|Name:|rosenbrock_func_data.mat|
|---|---|
| |rosenbrock_func_data.txt|
|Variable:|o 1*100 vector the shifted global optimum|

When cut using, o = o(1:D)
---
# 2.2.2. F₇: Shifted Rotated Griewank’s Function without Bounds

F₇(x) = ∑i=1D ∏i=14000 (zi - oi) - cos(zi) + 1 + fbias₇, z = (x - o) * M, x = [x1, x2,..., xD]

D: dimensions

o = [o1, o2,...,oD] : the shifted global optimum

M’ : linear transformation matrix, condition number = 3

M = M’(1 + 0.3|N(0,1)|)

# Properties:

- Multi-modal
- Rotated
- Shifted
- Non-separable
- Scalable
- No bounds for variables x
- Initialize population in [0, 600] D, Global optimum x* = o is outside of the initialization range, F₇(x*) = fbias₇ = -180

# Associated Data file:

|Name:|griewank_func_data.mat|griewank_func_data.txt|
|---|---|---|
|Variable:|o|1*100 vector|
|When cut using:|o = o(1:D)| |
|Name:|griewank_M_D10.mat|griewank_M_D10.txt|
|Variable:|M|10*10 matrix|
|Name:|griewank_M_D30.mat|griewank_M_D30.txt|
|Variable:|M|30*30 matrix|
|Name:|griewank_M_D50.mat|griewank_M_D50.txt|
|Variable:|M|50*50 matrix|

---
# 2.2.3. F₈: Shifted Rotated Ackley’s Function with Global Optimum on Bounds

F(x) = -20 exp(-0.2 * sqrt(1/D * ∑i=1D zi2)) - exp(1/D * ∑i=1D cos(2 * zi)) + 20 + e + fbias₈

z = (x - o) * M, x = [x1, x2,..., xD], D: dimensions

o = [o1, o2,..., oD]: the shifted global optimum; After loading the data file, set o2j−1 = -32 o2j are randomly distributed in the search range, for j = 1, 2,..., ⌊D/2⌋

M: linear transformation matrix, condition number = 100

# Figure 2-8 3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Rotated
- Shifted
- Non‑separable
- Scalable
- A’s condition number Cond(A) increases with the number of variables as O(D²)
- Global optimum on the bound
- If the initialization procedure initializes the population at the bounds, this problem will be solved easily.

x ∈ [-32, 32]D, Global optimum F(x) = fbias₈ = -140

# Associated Data file:

|Name:|ackley_func_data.mat|ackley_func_data.txt|
|---|---|---|
|Variable:|o|1*100 vector|
|When using,|oo = (1:D)| |
|Name:|ackley_M_D10.mat|ackley_M_D10.txt|
|Variable:|M|10*10 matrix|
|Name:|ackley_M_D30.mat|ackley_M_D30.txt|
|Variable:|M|30*30 matrix|
|Name:|ackley_M_D50.mat|ackley_M_D50.txt|
|Variable:|M|50*50 matrix|

---
# 2.2.4. F₉: Shifted Rastrigin’s Function

F9(x) = ∑i=1D zi2 - 10πzi + fbias

x = x1, x2, ..., xD, z = x - o, [1, 2, ..., D]

D: dimensions

o = [o1, o2, ..., oD]: the shifted global optimum

# Properties:

- Multi‑modal
- Shifted
- Separable
- Scalable
- Local optima’s number is huge

x ∈ [-5, 5]D <br />
x* = o <br />
F9(x*) = fbias <br />
Global optimum, F9(x) = -330

# Associated Data file:

|Name:|rastrigin_func_data.mat|
|---|---|
| |rastrigin_func_data.txt|
|Variable:|o 1*100 vector|
| |the shifted global optimum|
|When cut using,|o = (1: D)|
| |12|

---
# 2.2.5. F₁₀: Shifted Rotated Rastrigin’s Function

F10(x) = &sum;i=1D zi - πzi + fbias
z = x - o
M
x = x x x

D: dimensions

o = [o1, o2,...,oD] : the shifted global optimum

M: linear transformation matrix, condition number = 2

|Figure 2-10 3‑D map for 2‑D function|Figure 2-10 3‑D map for 2‑D function|Figure 2-10 3‑D map for 2‑D function|Figure 2-10 3‑D map for 2‑D function|
|---|---|---|---|
|100|200|300|400|

# Properties:

- Multi‑modal
- Shifted
- Rotated
- Non‑separable
- Scalable
- Local optima’s number is huge

x ∈ [-D, D]

x* = o

F(x*) = fbias

Global optimum = -330

# Associated Data file:

|Name:|rastrigin_func_data.mat|
|---|---|
| |rastrigin_func_data.txt|
|Variable:|o 1*100 vector the shifted global optimum|
|When cut using,|o = (1: D)|
|Name:|rastrigin_M_D10.mat|
| |rastrigin_M_D10.txt|
|Variable:|M 10*10 matrix|
|Name:|rastrigin_M_D30.mat|
| |rastrigin_M_D30.txt|
|Variable:|M 30*30 matrix|
|Name:|rastrigin_M_D50.mat|
| |rastrigin_M_D50.txt|
|Variable:|M 50*50 matrix|

---
# 2.2.6. F₁₁: Shifted Rotated Weierstrass Function

F11(x) = &sum;i=1&sum;k=0 ak πb z + &minus; D &sum;k=0 ak πb &sdot; + fbias

a = 0.5, b = 3, kmax = 20, z = x &minus; oM x = x x x

D: dimensions

o = [o1, o2, ..., oD]: the shifted global optimum

M: linear transformation matrix, condition number = 5

# Properties:

- Multi-modal
- Shifted
- Rotated
- Non-separable
- Scalable
- Continuous but differentiable only on a set of points

x &in; [0.5, 0.5], Global optimum x* = o, F11(x*) = fbias = 90

# Associated Data file:

|Name:|weierstrass_data.mat|weierstrass_data.txt|
|---|---|---|
|Variable:|o|1*100 vector|
|When cut using,|oD = (1: )| |
|Name:|weierstrass_M_D10.mat|weierstrass_M_D10.txt|
|Variable:|M|10*10 matrix|
|Name:|weierstrass_M_D30.mat|weierstrass_M_D30.txt|
|Variable:|M|30*30 matrix|
|Name:|weierstrass_M_D50.mat|weierstrass_M_D50.txt|
|Variable:|M|50*50 matrix|

---
# 2.2.7. F₁₂: Schwefel’s Problem 2.13

F12(x) = ∑i=1D A - B + fbias(x) = x12(x)i

A = ∑i=1D(aij sin αj + bij cos αj),
B = ∑i=1D xi = (aij sin xj + bij cos xj)

D: dimensions

A, B are two D*D matrices, aij, bij are integer random numbers in the range [-100,100],
α = [α1, α2, ..., αD], αj are random numbers in the range [-π,π].

# Figure 2-12

3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Shifted
- Non‑separable
- Scalable

x ∈ [-π, π]D, Global optimum * F12(*) = -460

# Associated Data file:

Name: schwefel_213_data.mat

schwefel_213_data.txt

Variable:

alpha: 1*100 vector the shifted global optimum

a: 100*100 matrix

b: 100*100 matrix

When using, alphai = (1: D), ai = (1: D, 1: D), bi = (1: D, 1: D)

In schwefel_213_data.txt, line 1-line 100 is a (100*100 matrix), and line 101-line 200 is b (100*100 matrix),
the last line is alpha (1*100 vector).
---
# 2.3 Expanded Functions

Using a 2‑D function Fx y(, ) as a starting function, corresponding expanded function is:

EFx = F1(x) + F2(x) + ... + FD(x)

F1(x) F2(x) ... FD-1(x) FD(x1, x2, ..., xD)

# 2.3.1 F13: Shifted Expanded Griewank’s plus Rosenbrock’s Function (F8F2)

F8: Griewank’s Function: F8(x) = ∑i=14000 (xi - ∏i=1D-1 cos( xi)) + 1

F2: Rosenbrock’s Function: F2(x) = ∑i=1D-1 (100(xi2 - xi+12)2 + (xi - 1)2)

F8F2(x1, x2, ..., xD) = F8(F2(x1, x2)) + F8(F2(x2, x3)) + ... + F8(F2(xD-1, xD)) + F8(F2(xD, x1))

Shift to

F13(x) = F8(F2(z1, z2)) + F8(F2(z2, z3)) + ... + F8(F2(zD-1, zD)) + F8(F2(zD, z1)) + fbias13

z = x - o + 1, x = [x1, x2, ..., xD]

D: dimensions o = [o1, o2, ..., oD]: the shifted global optimum

| |100|110|120|130| |
|---|---|---|---|---|---|
| |1.5|-1.8|1.6|-1.4|11.2|

# Properties:

- Multi‑modal
- Shifted
- Non‑separable
- Scalable

x ∈ [-5, 5], Global optimum x* = o, F13(x*) = fbias13 = -130

# Associated Data file:

Name: EF8F2_func_data.mat

Name: EF8F2_func_data.txt

Variable: o 1*100 vector the shifted global optimum

When cut using, o = (1:D)

16
---
# 2.3.2. F₁₄: Shifted Rotated Expanded Scaffer’s F6 Function

F(x, y) = 0.5 + (1 + 0.001(x² + y²))²

Expanded to

F(x) = EF(z) + F(z₁) + F(z₂) + ... + F(zD)

z = (x − o) * M, x = [x₁, x₂, ..., xD]

D: dimensions

o = [o₁, o₂, ..., oD]: the shifted global optimum

M: linear transformation matrix, condition number = 3

# Figure 2-14 3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Shifted
- Non‑separable
- Scalable

x ∈ [−100, 100]ᴰ, Global optimum x = o, F(*) f_bias(14) = -300

# Associated Data file:

|Name:|E_ScafferF6_func_data.mat|E_ScafferF6_func_data.txt|
|---|---|---|
|Variable:|o|1*100 vector|
|When cut using,|o = (1:D)| |
|Name:|E_ScafferF6_M_D10.mat|E_ScafferF6_M_D10.txt|
|Variable:|M|10*10 matrix|
|Name:|E_ScafferF6_M_D30.mat|E_ScafferF6_M_D30.txt|
|Variable:|M|30*30 matrix|
|Name:|E_ScafferF6_M_D50.mat|E_ScafferF6_M_D50.txt|
|Variable:|M|50*50 matrix|

---
 2.4   Composition functions
  F( ) : new composition function
     x
  f  x   th
  i ( ) : i  basic function used to construct the composition function
 n : number of basic functions
  D: dimensions
 Mi : linear transformation matrix for each   fi( x)
 oi : new shifted optimum position for each   fi (x)
                               n
                       F( ) ∑                       λ
                         x  =    {wi *[ fi '((x −oi ) / i * Mi ) +biasi ]}+ f _ bias
                               i=1
 w : weight value for each   f x
   i                          i ( ), calculated as below:
                                          D
                                         ∑(ˣₖ − oik )²
                             wi = exp(−  k=1 2Dσi2    ) ，
                             w    ⎧          wi           wi == max(wi)
                               i = ⎨w *(1‑max(w ).^10)     w ≠ max(w )
                                  ⎩  i           i           i         i
                                                                   n
                              then normalize the weight  wi = wi  / ∑ wi
                                                                  i=1
 σ : used to control each  f  x                             σ                                        x
   i                        i ( )’s coverage range, a small       i  give a narrow range for that fi ( )
 λi  : used to stretch compress the function, λi >1 means stretch, λi <1 means compress
 oi  define the global and local optima’s position,  biasi  define which optimum is global optimum.
Using  oi ,  biasi , a global optimum can be placed anywhere.
 If ( )x
    fi    are different functions, differe nt functions have different pr operties and height, in order
 to get a better mixture, esti  mate a biggest function value     f                          x
                                                                      for 10 functions    ( )
                                                                  maxi                    fi   , then
 normalize each basic functions to similar heights as below:
  f  x          x         , C is a predefined constant.
  i '( ) = C * fi ( ) / fₘₐₓi
 fₘₐₓi  is estimated using  fₘₐₓi = fi((x'/ λi )*Mi ), x'=[5,5…,5].
 In the following composition functions,
 Number of basic functions n=10.
 D: dimensions
 o: n*D matrix, defines  f  x
                          i ( ) ’s global optimal positions
      =[0, 100, 200, 300, 400, 500, 600, 700, 800, 900]. Hence, the first function   f x
 bias                                                                                 1( ) always the
 function with the global optimum.
 C=2000
                                                  18
---
# Pseudo Code:

Define f1‑f10, σ, λ, bias, C, load data file o and rotated linear transformation matrix M1‑M10

y =[5,5…,5].

For i=1:10

D

w = exp(− ∑(xᵏ − oⁱᵏ )² ) ，

k=1

i

2Dσi²

fiti = fi (((x −oi ) / λi )*Mi)

f maxi = fi((y / λi ) *Mi) ,

fiti = C * fiti / f maxi

EndFor

n

SW = ∑ wi

i=1

MaxW = max(wi)

For i=1:10

w ⎧         wi           if                  wi == MaxW

= ⎨w *(1‑MaxW .^10)  if             w ≠ MaxW

⎩    i                        i

wi = wi  / SW

EndFor

n

F x     ∑

( ) =   {wi *[ fiti + biasi ]}

i=1

F x =       +

( )    F (x) f _ bias

19
---
# 2.4.1. F₁₅: Hybrid Composition Function

f1(x) : Rastrigin’s Function

f1(x) = &sum;i=1D (xi2 - 10 cos(2 xi) + 10)

f3−4(x) : Weierstrass Function

fi(x) = &sum;i=1D &sum;k=0kmax (ak cos(2bk(xi + 0.5))) - D &sum;k=0kmax (ak cos(2bk ⋅ 0.5))

a = 0.5, b = 3, kmax = 20

f5−6(x) : Griewank’s Function

fi(x) = &sum;i=1D (xi2 / 4000 - &prod;i=1D cos(xi / &sqrt;i) + 1)

f7−8(x) : Ackley’s Function

fi(x) = -20 exp(-0.2 &sum;i=1D xi2) - exp(&sum;i=1D cos(2 xi)) + 20 + e

f9−10(x) : Sphere Function

fi(x) = &sum;i=1D xi2

σi = 1 for i = 1, 2,..., D

λ = [1, 1, 10, 10, 5/60, 5/60, 5/32, 5/32, 5/100, 5/100]

Mi are all identity matrices

Please notice that these formulas are just for the basic functions, no shift or rotation is included in these expressions. x here is just a variable in a function.

Take f1 as an example, when we calculate λ1 f1(((x - o1) / 1) * M1), we need to calculate:

f1(z) = &sum;i=1D (zi2 - 10 cos(2 zi) + 10), z = ((x - o1) / 1) * M1.
---
# Figure 2-15 3‑D map for 2‑D function

3000250020005000o0500
# Properties:

- Multi‑modal
- Separable near the global optimum (Rastrigin)
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function x ∈ −[5,5]ᴰ, Global optimum x* = o₁, F (x*) = f_bias = 120

# Associated Data file:

|Name:|hybrid_func1_data.mat|
|---|---|
| |hybrid_func1_data.txt|
|Variable:|o 10*100 vector the shifted optimum for 10 functions|
|When cut using,|o=o(:,1:D)|

---
# 2.4.2. F₁₆: Rotated Version of Hybrid Composition Function F₁₅

Except Mi are different linear transformation matrixes with condition number of 2, all other settings are the same as F15.

Figure 2-16 3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Rotated
- Non‑Separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function.
- x ∈ [−5,5]ᴰ, Global optimum x* = o₁, F (x*) = f_bias = 120

# Associated Data file:

|Name:|hybrid_func1_data.mat|
|---|---|
| |hybrid_func1_data.txt|
|Variable:|o 10*100 vector the shifted optima for 10 functions|
| |When using, cut o=o(:,1:D)|
|Name:|hybrid_func1_M_D10.mat|
|Variable:|M structure an variable|
| |Contains M.M1 M.M2, … , M.M10 ten 10*10 matrixes|
|Name:|hybrid_func1_M_D10.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 10*10 matrixes, 1‑10 lines are M1, 11‑20 lines are M2,....,91‑100 lines are M10|
|Name:|hybrid_func1_M_D30.mat|
|Variable:|M structure an variable contains M.M1,…,M.M10 ten 30*30 matrix|
|Name:|hybrid_func1_M_D30.txt|

---
# Variable

M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 30*30 matrixes, 1‑30 lines are M1, 31‑60 lines are M2,....,271‑300 lines are M10

# Name

hybrid_func1_M_D50 .mat

# Variable

M

structure

an variable contains M.M1,…,M.M10 ten 50*50 matrix

# Name

hybrid_func1_M_D50 .txt

# Variable

M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 50*50 matrixes, 1‑50 lines are M1, 51‑100 lines are M2,....,451‑500 lines are M10
---
# 2.4.3. F₁₇: F₁₆ with Noise in Fitness

Let (F₁₆ ‑ f_bias₁₆) be G(x), then

F17(x) = G(x) * (1 + 0.2 N(0,1)) + fbias

All settings are the same as F₁₆.

# Properties:

- Multi‑modal
- Rotated
- Non‑Separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function.
- With Gaussian noise in fitness
- x ∈ [−5,5]D, Global optimum x* = o₁, F17(x*) = fbias = 120

# Associated Data file:

Same as F₁₆.
---
# 2.4.4. F₁₈: Rotated Hybrid Composition Function

# f1(x)

Ackley’s Function

f1(x) = -20 exp( -0.2 &sum;i=1D xi2) - exp(&sum;i=1D cos(2 &pi; xi)) + 20

# f3-4(x)

Rastrigin’s Function

f3-4(x) = &sum;i=1D (xi2 - 10 cos(2 &pi; xi) + 10)

# f5-6(x)

Sphere Function

f5-6(x) = &sum;i=1D xi2

# f7-8(x)

Weierstrass Function

f7-8(x) = &sum;i=1D &sum;k=0kmax [ak cos(2 bk (xi + 0.5))] - D &sum;k=0kmax [ak cos(2 bk * 0.5)], a=0.5, b=3, kmax=20

# f9-10(x)

Griewank’s Function

f9-10(x) = &sum;i=1D (xi2/4000) - &prod;i=1D cos(xi/&radic;i) + 1

σ = [1, 2, 1.5, 1.5, 1, 1, 1.5, 1.5, 2, 2];

λ = [2*5/32; 5/32; 2*1; 1; 2*5/100; 5/100; 2*10; 10; 2*5/60; 5/60]

Mi are all rotation matrices. Condition numbers are [2, 3, 2, 3, 2, 3, 20, 30, 200, 300]

o10 = [0, 0,..., 0]

# Figure 2-18

3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Rotated
- Non‑Separable
- Scalable
---
# Current Page Content

- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function.
- A local optimum is set on the origin
- x ∈ − D
- [5,5], Global optimum x = o₁, F(x) = f_bias = 10

# Associated Data file:

|Name:|hybrid_func2_data.mat|
|---|---|
| |hybrid_func2_data.txt|
|Variable:|o 10*100 vector the shifted optima for 10 functions|
| |When using, cut o=o(:,1:D)|
|Name:|hybrid_func2_M_D10.mat|
|Variable:|M structure an variable|
| |Contains M.M1 M.M2, … , M.M10 ten 10*10 matrixes|
|Name:|hybrid_func2_M_D10.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 10*10 matrixes, 1‑10 lines are M1, 11‑20 lines are M2,....,91‑100 lines are M10|
|Name:|hybrid_func2_M_D30.mat|
|Variable:|M structure an variable contains M.M1,…,M.M10 ten 30*30 matrix|
|Name:|hybrid_func2_M_D30.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 30*30 matrixes, 1‑30 lines are M1, 31‑60 lines are M2,....,271‑300 lines are M10|
|Name:|hybrid_func2_M_D50.mat|
|Variable:|M structure an variable contains M.M1,…,M.M10 ten 50*50 matrix|
|Name:|hybrid_func2_M_D50.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 50*50 matrixes, 1‑50 lines are M1, 51‑100 lines are M2,....,451‑500 lines are M10|

---
# 2.4.5. F₁₉: Rotated Hybrid Composition Function with narrow basin global optimum

All settings are the same as F₁₈ except

σ = [0.1, 2, 1.5, 1.5, 1, 1, 1.5, 1.5, 2, 2];

λ = [0.1*5/32; 5/32; 2*1; 1; 2*5/100; 5/100; 2*10; 10; 2*5/60; 5/60]

30002500200015001000500
Figure 2-19 3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Non‑separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function.
- A local optimum is set on the origin
- A narrow basin for the global optimum
- x ∈ [−5, 5]ᴰ, Global optimum x* = o₁, F₁₉(x*) = f_bias (19) = 10

Associated Data file:

Same as F₁₈.

27
---
# 2.4.6. F₂₀: Rotated Hybrid Composition Function with Global Optimum on the Bounds

All settings are the same as F₁₈ except after load the data file, set o₁(2j) = 5, for j = 1, 2,..., ⎢D / 2⎥

# Properties:

- Multi‑modal
- Non‑separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Sphere Functions give two flat areas for the function.
- A local optimum is set on the origin
- Global optimum is on the bound
- If the initialization procedure initializes the population at the bounds, this problem will be solved easily.
- x ∈ − D * *
- [ 5,5], Global optimum x = o₁, F₂₀(x) = f_bias₂₀ = 10

# Associated Data file:

Same as F18.
---
# 2.4.7. F₂₁: Rotated Hybrid Composition Function

f1(x): Rotated Expanded Scaffer’s F6 Function

F(x, y) = 0.5 + (sin(x2 + y2) − 0.5)2 (1 + 0.001(x2 + y2))2

f2(x) = F1(x1, x) + F2(x2, x) + ... + FD-1(xD, x)

f3-4(x): Rastrigin’s Function

fi(x) = ∑i=1D (xi2 − 10 cos(2 xi) + 10)

f5-6(x): F8F2 Function

F8(x) = ∑i=1D (xi2 − cos(4000 xi)) + 1

F2(x) = ∑i=1D-1 (100(xi2 − xi+12)2 + (xi − 1)2)

fi(x) = F8(F2(x1, x2)) + F8(F2(x2, x3)) + ... + F8(F2(xD-1, xD)) + F8(F2(xD, x1))

f7-8(x): Weierstrass Function

fi(x) = ∑i=1D ∑k=0kmax (ak cos(2 bk (xi + 0.5))) − D ∑k=0kmax (ak cos(2 bk ⋅ 0.5))

a = 0.5, b = 3, kmax = 20

f9-10(x): Griewank’s Function

fi(x) = ∑i=1D (xi2 − cos(4000 xi)) + 1

σ = [1, 1, 1, 1, 1, 2, 2, 2, 2, 2],
λ = [5*5/100; 5/100; 5*1; 1; 5*1; 1; 5*10; 10; 5*5/200; 5/200];

Mi are all orthogonal matrix
---
# Properties:

- Multi‑modal
- Rotated
- Non‑Separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together

x ∈ [−5,5]ᴰ, Global optimum x* = o₁, F₂₁(x*) = f_bias₂₁ = 360

# Associated Data file:

|Name:|hybrid_func3_data.mat|
|---|---|
| |hybrid_func3_data.txt|
|Variable:|o 10*100 vector the shifted optima for 10 functions|
| |When using, cut o=o(:,1:D)|
|Name:|hybrid_func3_M_D10.mat|
|Variable:|M structure an variable|
| |Contains M.M1 M.M2, … , M.M10 ten 10*10 matrixes|
|Name:|hybrid_func3_M_D10.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 10*10 matrixes, 1‑10 lines are M1, 11‑20 lines are M2,....,91‑100 lines are M10|
|Name:|hybrid_func3_M_D30.mat|
|Variable:|M structure an variable contains M.M1,…,M.M10 ten 30*30 matrix|
|Name:|hybrid_func3_M_D30.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 30*30 matrixes, 1‑30 lines are M1, 31‑60 lines are M2,....,271‑300 lines are M10|
|Name:|hybrid_func3_M_D50.mat|
|Variable:|M structure an variable contains M.M1,…,M.M10 ten 50*50 matrix|
|Name:|hybrid_func3_M_D50.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 50*50 matrixes, 1‑50 lines are M1, 51‑100 lines are M2,....,451‑500 lines are M10|

---
# 2.4.8. F₂₂: Rotated Hybrid Composition Function with High Condition Number Matrix

All settings are the same as F₂₁ except  Mi ’s condition numbers are [10 20 50 100 200 1000 2000 3000 4000 5000 10000]

# Properties:

- Multi‑modal
- Non‑separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Global optimum is on the bound
- x ∈ [−5,5]ᴰ, Global optimum x* = o₁, F₂₂(x*) = f_bias₂₂ = 360

# Associated Data file:

|Name:|hybrid_func3_data.mat|
|---|---|
| |hybrid_func3_data.txt|
|Variable:|o 10*100 vector the shifted optima for 10 functions|
| |When using, cut o=o(:,1:D)|
|Name:|hybrid_func3_HM_D10.mat|
|Variable:|M structure an variable|
| |Contains M.M1 M.M2, … , M.M10 ten 10*10 matrixes|
|Name:|hybrid_func3_HM_D10.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 10*10 matrixes, 1‑10 lines are M1, 11‑20 lines are M2,....,91‑100 lines are M10|
|Name:|hybrid_func3_HM_D30.mat|
|Variable:|M an structure variable contains M.M1,…,M.M10 ten 30*30 matrix|
|Name:|hybrid_func3_MH_D30.txt|
|Variable:|M1 M2 M3 M4 M5 M6 M7 M8 M9 M10 are ten 30*30 matrixes, 1‑30 lines are M1, 31‑60 lines are M2,....,271‑300 lines are M10|

---
# Name: hybrid_func3_MH_D50 .mat

# Variable: M

structure an variable contains M.M1,…,M.M10 ten 50*50 matrix

# Name: hybrid_func3_HM_D50 .txt

# Variable: M1 M2 M3 M4 M5 M6 M7 M8 M9 M10

are ten 50*50 matrixes, 1‑50 lines are M1, 51‑100 lines are M2,....,451‑500 lines are M10

32
---
# 2.4.9. F₂₃: Non-Continuous Rotated Hybrid Composition Function

All settings are the same as F₂₁.

⎧ x
x − o   < 1/2

Except  x
⎪   j
j   1j

= ⎨
for 1, 2,..,

j
⎪round(2x  ) / 2 x  −o   >= 1/2
j =      D

⎩
j

⎧a −1   if         x <= 0 & b >= 0.5

round x
⎪                            ,

( ) = ⎨ a
if              b < 0.5

⎪a +1   if          x > 0 &b >= 0.5

⎩

where a is  x ’s integral part and b is  x ’s decimal part

All “round” operators in this document use the same schedule.

eoo0
4000
3000
zuoo
1000

Figure 2-23 3‑D map for 2‑D function

# Properties:

- ¾ Multi‑modal
- ¾ Non‑separable
- ¾ Scalable
- ¾ A huge number of local optima
- ¾ Different function’s properties are mixed together
- ¾ Non‑continuous
- ¾ Global optimum is on the bound

x ∈ −                       x   o      x     f_bias

¾      [ 5,5]ᴰ , Global optimum  * =  1 , f ( * ) ≈    (23)=360

# Associated Data file:

Same as F₂₁.

33
---
# 2.4.10. F₂₄: Rotated Hybrid Composition Function

f1(x): Weierstrass Function

fi(x) = (Dkmax ∑i=1 ∑k=0 π [ak cos(2 bk (xi + 0.5))]) − D [ak cos(2 bk 0.5)],

a = 0.5, b = 3, kmax = 20

f2(x): Rotated Expanded Scaffer’s F6 Function

F(x, y) = 0.5 + (sin(x2 + y2) − 0.5)2 + (1 + 0.001(x2 + y2))2

fi(x) = F(x1, x) + F(x2, x) + ... + F(xD, x)

f3(x): F8F2 Function

F8(x) = ∑i=1D xi2 − ∏i=14000 cos(xi) + 1

F2(x) = ∑i=1D−1 (100(xi2 − xi+12)2 + (xi − 1)2)

fi(x) = F8(F2(x1, x2)) + F8(F2(x2, x3)) + ... + F8(F2(xD−1, xD)) + F8(F2(xD, x1))

f4(x): Ackley’s Function

fi(x) = −20 exp(−0.2 ∑i=1D xi2) − exp(∑i=1D cos(2 π xi)) + 20 + e

f5(x): Rastrigin’s Function

fi(x) = ∑i=1D (xi2 − 10 cos(2 xi) + 10)

f6(x): Griewank’s Function

fi(x) = ∑i=1D xi2 − ∏i=14000 cos( xi) + 1

f7(x): Non‑Continuous Expanded Scaffer’s F6 Function

F(x, y) = 0.5 + (sin(x2 + y2) − 0.5)2 + (1 + 0.001(x2 + y2))2

f(x) = F(y1, y) + F(y2, y) + ... + F(yD, y)

yj =

⎧ xj
j = 1, 2, .., D

⎨ round(2xj) / 2
xj >= 1/2
⎩

f8(x): Non‑Continuous Rastrigin’s Function

fi(x) = ∑i=1D (yi2 − 10 cos(2 yi) + 10)
---
# 9 ( ): High Conditioned Elliptic Function

fx = ∑i=1D 6i (10)D−¹ xi

# 10( ): Sphere Function with Noise in Fitness

fx = ∑i=1D (xi)(1 + 0.1 N(0,1))

σ = 2, for 1, 2...,

i = D

λ = [10; 5/20; 1; 5/32; 1; 5/100; 5/50; 1; 5/100; 5/100]

Mi are all rotation matrices, condition numbers are [100 50 30 10 5 5 4 3 2 2];

# Figure 2-24 3‑D map for 2‑D function

# Properties:

- Multi‑modal
- Rotated
- Non‑Separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Unimodal Functions give flat areas for the function.

x ∈ −D

x*o = 1, F24(x) = fbias₂₄ = 260

# Associated Data file:

Name: hybrid_func4_data.mat

hybrid_func4_data.txt

Variable: o 10*100 vector the shifted optima for 10 functions

When using, cut o=o(:,1:D)
---
# Hybrid Function Matrices

# 1. hybrid_func4_M_D10

File Type: .mat

Variable: M

Structure: an variable

Contains M.M1, M.M2, … , M.M10 ten 10*10 matrixes

# 2. hybrid_func4_M_D10.txt

Variable: M1, M2, M3, M4, M5, M6, M7, M8, M9, M10 are ten 10*10 matrixes,

1‑10 lines are M1, 11‑20 lines are M2,....,91‑100 lines are M10

# 3. hybrid_func4_M_D30

File Type: .mat

Variable: M

Structure: an variable

Contains ten 30*30 matrix

# 4. hybrid_func4_M_D30.txt

Variable: M1, M2, M3, M4, M5, M6, M7, M8, M9, M10 are ten 30*30 matrixes,

1‑30 lines are M1, 31‑60 lines are M2,....,271‑300 lines are M10

# 5. hybrid_func4_M_D50

File Type: .mat

Variable: M

Structure: an variable

Contains ten 50*50 matrix

# 6. hybrid_func4_M_D50.txt

Variable: M1, M2, M3, M4, M5, M6, M7, M8, M9, M10 are ten 50*50 matrixes,

1‑50 lines are M1, 51‑100 lines are M2,....,451‑500 lines are M10
---
# 2.4.11. F₂₅: Rotated Hybrid Composition Function without bounds

All settings are the same as F₂₄ except no exact search range set for this test function.

# Properties:

- Multi‑modal
- Non‑separable
- Scalable
- A huge number of local optima
- Different function’s properties are mixed together
- Unimodal Functions give flat areas for the function.
- Global optimum is on the bound
- No bounds

Initialize population in [2,5], Global optimum = D x* o₁ is outside of the initialization range, F₂₅(x* ) = f_bias₂₅ = 260

# Associated Data file:

Same as F₂₄

37
---
# 2.5 Comparisons Pairs

# Different Condition Numbers:

- F₁. Shifted Rotated Sphere Function
- F₂. Shifted Schwefel’s Problem 1.2
- F₃. Shifted Rotated High Conditioned Elliptic Function

# Function With Noise Vs Without Noise

# Pair 1:

- F₂. Shifted Schwefel’s Problem 1.2
- F₄. Shifted Schwefel’s Problem 1.2 with Noise in Fitness

# Pair 2:

- F₁₆. Rotated Hybrid Composition Function
- F₁₇. F₁₆. with Noise in Fitness

# Function without Rotation Vs With Rotation

# Pair 1:

- F₉. Shifted Rastrigin’s Function
- F₁₀. Shifted Rotated Rastrigin’s Function

# Pair 2:

- F₁₅. Hybrid Composition Function
- F₁₆. Rotated Hybrid Composition Function

# Continuous Vs Non-continuous

- F₂₁. Rotated Hybrid Composition Function
- F₂₃. Non‑Continuous Rotated Hybrid Composition Function

# Global Optimum on Bounds Vs Global Optimum on Bounds

- F₁₈. Rotated Hybrid Composition Function
- F₂₀. Rotated Hybrid Composition Function with the Global Optimum on the Bounds

# Wide Global Optimum Basin Vs Narrow Global Optimum Basin

- F₁₈. Rotated Hybrid Composition Function
- F₁₉. Rotated Hybrid Composition Function with a Narrow Basin for the Global Optimum

# Orthogonal Matrix Vs High Condition Number Matrix

- F₂₁. Rotated Hybrid Composition Function
- F₂₂. Rotated Hybrid Composition Function with High Condition Number Matrix

# Global Optimum in the Initialization Range Vs outside of the Initialization Range

- F₂₄. Rotated Hybrid Composition Function
- F₂₅. Rotated Hybrid Composition Function without Bounds
---
# 2.6 Similar Groups:

# Unimodal Functions

Function 1‑5

# Multi-modal Functions

Function 6‑25

- Single
- Function:
- Function 6‑12

Expanded
- Function:
- Function 13‑14

Hybrid Composition Function:

# Functions with Global Optimum outside of the Initialization Range

- F₇. Shifted Rotated Griewank’s Function without Bounds
- F₂₅. Rotated Hybrid Composition Function 4 without Bounds

# Functions with Global Optimum on Bounds

- F₅. Schwefel’s Problem 2.6 with Global Optimum on Bounds
- F₈. Shifted Rotated Ackley’s Function with Global Optimum on Bounds
- F₂₀. Rotated Hybrid Composition Function 2 with the Global Optimum on the Bounds

39
---
# 3. Evaluation Criteria

# 3.1 Description of the Evaluation Criteria

Problems:

- minimization
- 25 problems
- Dimensions: D=10, 30, 50

Runs / problem: 25 (Do not run many 25 runs to pick the best run)

Max_FES: 10000*D (Max_FES_10D= 100000; for 30D=300000; for 50D=500000)

Initialization: Uniform random initialization within the search space, except for problems 7 and 25, for which initialization ranges are specified.

Please use the same initializations for the comparison pairs (problems 1, 2, 3 & 4, problems 9 & 10, problems 15, 16 & 17, problems 18, 19 & 20, problems 21, 22 & 23, problems 24 & 25). One way to achieve this would be to use a fixed seed for the random number generator.

Global Optimum: All problems, except 7 and 25, have the global optimum within the given bounds and there is no need to perform search outside of the given bounds for these problems. 7 & 25 are exceptions without a search range and with the global optimum outside of the specified initialization range.

Termination: Terminate before reaching Max_FES if the error in the function value is 10‑8 or less.

Ter_Err: 10‑8 (termination error value)

1. Record function error value (f(x)-f(x*)) after 1e3, 1e4, 1e5 FES and at termination (due to Ter_Err or Max_FES) for each run. For each function, sort the error values in 25 runs from the smallest (best) to the largest (worst). Present the following: 1ˢᵗ (best), 7ᵗʰ, 13ᵗʰ (median), 19ᵗʰ, 25ᵗʰ (worst) function values Mean and STD for the 25 runs.
2. Record the FES needed in each run to achieve the following fixed accuracy level. The Max_FES applies.

**Table 3-1 Fixed Accuracy Level for Each Function**
|Function|Accuracy|
|---|---|
|1|‑450 + 1e‑6|
|14|‑300 + 1e‑2|
|40| |

---
|2|-450 + 1e-6|15|120 + 1e-2|
|---|---|---|---|
|3|-450 + 1e-6|16|120 + 1e-2|
|4|-450 + 1e-6|17|120 + 1e-1|
|5|-310 + 1e-6|18|10 + 1e-1|
|6|390 + 1e-2|19|10 + 1e-1|
|7|-180 + 1e-2|20|10 + 1e-1|
|8|-140 + 1e-2|21|360 + 1e-1|
|9|-330 + 1e-2|22|360 + 1e-1|
|10|-330 + 1e-2|23|360 + 1e-1|
|11|90 + 1e-2|24|260 + 1e-1|
|12|-460 + 1e-2|25|260 + 1e-1|
|13|-130| | |

Successful Run: A run during which the algorithm achieves the fixed accuracy level within the Max_FES for the particular dimension.

For each function/dimension, sort FES in 25 runs from the smallest (best) to the largest (worst)

Present the following: 1st (best), 7th, 13th (median), 19th, 25th (worst) FES

Mean and STD for the 25 runs

# 3) Success Rate & Success Performance For Each Problem

Success Rate= (# of successful runs according to the table above) / total runs

Success Performance=mean (FEs for successful runs)*(# of total runs) / (# of successful runs)

The above two quantities are computed for each problem separately.

# 4) Convergence Graphs (or Run-length distribution graphs)

Convergence Graphs for each problem for D=30. The graph would show the median performance of the total runs with termination by either the Max_FES or the Ter_Err. The semi-log graphs should show log10(f(x) - f(x*)) vs FES for each problem.

# 5) Algorithm Complexity

a) Run the test program below:
---
for i=1:1000000

x= (double) 5.55;

x=x + x; x=x./2; x=x*x; x=sqrt(x); x=ln(x); x=exp(x); y=x/x;

end

Computing time for the above=T0;

b) evaluate the computing time just for Function 3. For 200000 evaluations of a certain dimension D, it gives T1;

c) the complete computing time for the algorithm with 200000 evaluations of the same D dimensional benchmark function 3 is T2. Execute step c 5 times and get 5 T2 values.

T 2 =Mean(T2)

The complexity of the algorithm is reflected by: T2 , T1, T0, and ( T2 -T1)/T0

The algorithm complexities are calculated on 10, 30 and 50 dimensions, to show the algorithm complexity’s relationship with dimension. Also provide sufficient details on the computing system and the programming language used. In step c, we execute the complete algorithm 5 times to accommodate variations in execution time due adaptive nature of some algorithms.

# 6) Parameters

We discourage participants searching for a distinct set of parameters for each problem/dimension/etc. Please provide details on the following whenever applicable:

a) All parameters to be adjusted

b) Corresponding dynamic ranges

c) Guidelines on how to adjust the parameters

d) Estimated cost of parameter tuning in terms of number of FEs

e) Actual parameter values used.

# 7) Encoding

If the algorithm requires encoding, then the encoding scheme should be independent of the specific problems and governed by generic factors such as the search ranges.

42
---
# 3.2 Example

System: Windows XP (SP1)

CPU: Pentium(R) 4 3.00GHz

RAM: 1 G

Language: Matlab 6.5

Algorithm: Particle Swarm Optimizer (PSO)

# Results

D=10

Max_FES=100000

| |Prob|8|1|2|3|4|5|
|---|---|---|---|---|---|---|---|
|FES|7|6| | | | | |
|1st(Best)|4.8672e+2|4.7296e+2|2.2037e+6|4.6617e+2|2.3522e+3| | |
|7th|8.0293e+2|9.8091e+2|8.5141e+6|1.2900e+3|4.0573e+3| | |
|13th(Median)|9.2384e+2|1.5293e+3|1.4311e+7|1.9769e+3|4.6308e+3| | |
|1e3|19th|1.3393e+3|1.7615e+3|1.9298e+7|2.9175e+3|4.8015e+3| |
|25th (Worst)|1.9151e+3|3.2337e+3|4.4688e+7|6.5038e+3|5.6701e+3| | |
|Mean|1.0996e+3|1.5107e+3|1.5156e+7|2.3669e+3|4.4857e+3| | |
|Std|4.0575e+2|7.2503e+2|9.3002e+6|1.5082e+3|7.0081e+2| | |
|1st(Best)|3.1984e‑3|1.0413e+0|1.3491e+5|6.7175e+0|1.6584e+3| | |
|7th|2.6509e‑2|1.3202e+1|4.4023e+5|3.8884e+1|2.3522e+3| | |
|13th(Median)|6.0665e‑2|1.9981e+1|1.1727e+6|5.5027e+1|2.6335e+3| | |
|1e4|19th|1.0657e‑1|3.5319e+1|2.0824e+6|7.1385e+1|2.8788e+3| |
|25th (Worst)|4.3846e‑1|1.0517e+2|2.9099e+6|1.7905e+2|3.6094e+3| | |
|Mean|8.6962e‑2|2.7883e+1|1.3599e+6|5.9894e+1|2.6055e+3| | |
|Std|9.6616e‑2|2.3526e+1|9.1421e+5|3.5988e+1|4.5167e+2| | |
|1st(Best)|4.7434e‑9T|5.1782e‑9T|4.2175e+4|1.7070e‑5|1.1864e+3| | |
|7th|7.9845e‑9T|8.5278e‑9T|1.2805e+5|1.2433e‑3|1.4951e+3| | |
|13th(Median)|9.0901e‑9T|9.7281e‑9T|2.3534e+5|4.0361e‑3|1.7380e+3| | |
|1e5|19th|9.6540e‑9T|1.5249e‑8|4.6436e+5|1.8283e‑2|1.9846e+3| |
|25th (Worst)|9.9506e‑9T|2.3845e‑7|2.2776e+6|3.9795e‑1|2.3239e+3| | |
|Mean|8.5375e‑9T|3.2227e‑8|4.6185e+5|3.4388e‑2|1.7517e+3| | |
|Std|1.4177e‑9T|6.2340e‑8|5.4685e+5|8.2733e‑2|2.9707e+2| | |

* xxx.e-9T means it get termination error before it gets the predefined record FES.
---
# Table 3-3 Error Values Achieved When FES=1e+3, FES=1e+4, FES=1e+5 for Problems 9‑17

|FES|Prob|9|10|11|12|13|14|15|16|17| | |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| | |1e+3|1ˢᵗ(Best)| | | | | | | | | |
| |7ᵗʰ| | | | | | | | | | | |
| |13ᵗʰ(Median)| | | | | | | | | | | |
| |19ᵗʰ| | | | | | | | | | | |
| |25ᵗʰ (Worst)| | | | | | | | | | | |
| |Mean| | | | | | | | | | | |
| |Std| | | | | | | | | | | |

# Table 3-4 Error Values Achieved When FES=1e+3, FES=1e+4, FES=1e+5 for Problems 18‑25

|FES|Prob|18|19|20|21|22|23|24|25| |
|---|---|---|---|---|---|---|---|---|---|---|
| |1e+3|1ˢᵗ(Best)| | | | | | | | |
|7ᵗʰ| | | | | | | | | | |
|13ᵗʰ| | | | | | | | | | |
|(Median)| | | | | | | | | | |
|19ᵗʰ| | | | | | | | | | |
|25ᵗʰ| | | | | | | | | | |
| |(Worst)| | | | | | | | | |
| |Mean| | | | | | | | | |
| |Std| | | | | | | | | |

---
# Table 3-5 Number of FES to achieve the fixed accuracy level

|Prob|1st(Best)|7th|13th|19th|25th|Mean|Std|Success rate|Success Performance|
|---|---|---|---|---|---|---|---|---|---|
|1|11607|12133|12372|12704|13022|1.2373e+4|3.6607e+2|100%|1.2373e+4|
|2|17042|17608|18039|18753|19671|1.8163e+4|7.5123e+2|100%|1.8163e+4|
|3|0%|-|-|-|-|-|-|-|-|
|4|0%|-|-|-|-|-|-|-|-|
|5|0%|-|-|-|-|-|-|-|-|

Max_FES=300000

# Table 3-6 Error Values Achieved When FES=1e3, FES=1e4, FES=1e5 for Problems 1-8

|FES|Prob|1st(Best)|7th|13th|(Median)|19th|25th|(Worst)|Mean|Std|
|---|---|---|---|---|---|---|---|---|---|---|
|1e3| | | | | | | | | | |
|1e4| | | | | | | | | | |
|1e5| | | | | | | | | | |

---
# Table 3-7

# Error Values Achieved When FES=1e3, FES=1e4, FES=1e5 for Problems 1-8

|FES|Prob|1st(Best)|7th|13th|(Median)|19th|25th(Worst)|Mean|Std|
|---|---|---|---|---|---|---|---|---|---|
|1e3| | | | | | | | | |
|1e4| | | | | | | | | |
|1e5| | | | | | | | | |
|3e5| | | | | | | | | |

---
# Convergence Graphs (30D)

| |1010|105|100|log(f(x)-f(x*))| | | |
|---|---|---|---|---|---|---|---|
| |10-5|function1|function2| | | | |
| |10-10|function3|function4|function5| | | |
| |0|0.5|1|1.5|2|2.5|3|

Figure 3-1 Convergence Graph for Functions 1‑5

Figure 3-2 Convergence Graph for Function 6‑10

Figure 3-3 Convergence Graph for Function 11‑14

Figure 3-4 Convergence Graph for Function 15‑20

Figure 3-5 Convergence Graph for Function 21‑25

# Algorithm Complexity

**Table 3-8 Computational Complexity**
|T0|T1| |( )|( )|-T1)/T0|T2|T2|
|---|---|---|---|---|---|---|---|
|1.2963|82.3906|D=10|31.1250| | | | |
|1.3331|90.8437|D=30|38.1250|39.5470| | | |
| |D=50| |46.0780|108.9094|1.5888| | |

---
# Parameters

- a) All parameters to be adjusted
- b) Corresponding dynamic ranges
- c) Guidelines on how to adjust the parameters
- d) Estimated cost of parameter tuning in terms of number of FES
- e) Actual parameter values used.
---
# 4. Notes

Note 1: Linear Transformation Matrix

M = P * N * Q

P, Q are two orthogonal matrixes, generated using Classical Gram‑Schmidt method

N is diagonal matrix

ui − min(u)

u = rand(1, D), dii = cmax(u) − min(u)

M’s condition number Cond(M) = c

Note 2: On page 17, wi values are sorted and raised to a higher power. The objective is to ensure that each optimum (local or global) is determined by only one function while allowing a higher degree of mixing of different functions just a very short distance away from each optimum.

Note 3: We assign different positive and negative objective function values, instead of zeros. This may influence some algorithms that make use of the objective values.

Note 4: We assign the same objective values to the comparison pairs in order to make the comparison easier.

Note 5: High condition number rotation may convert a multimodal problem into a unimodal problem. Hence, moderate condition numbers were used for multimodal.

Note 6: Additional data files are provided with some coordinate positions and the corresponding fitness values in order to help the verification process during the code translation.

Note 7: It is insufficient to make any statistically meaningful conclusions on the pairs of problems as each case has at most 2 pairs. We would probably require 5 or 10 or more pairs for each case. We would consider this extension for the edited volume.

Note 8: Pseudo‑real world problems are available from the web link given below. If you have any queries on these problems, please contact Professor Darrell Whitley directly. Email: whitley@CS.ColoState.EDU

Web-link: http://www.cs.colostate.edu/~genitor/functions.html

Note 9: We are recording the numbers such as ‘the number of FES to reach the given fixed accuracy’, ‘the objective function value at different number of FES’ for each run of each problem and each dimension in order to perform some statistical significance tests. The details of a statistical significance test would be made available a little later.
---
# References:

1. N. Hansen, S. D. Muller and P. Koumoutsakos, “Reducing the Time Complexity of the Derandomized evolution Strategy with Covariance Matrix Adaptation (CMA‑ES).” Evolutionary Computation, 11(1), pp. 1‑18, 2003
2. A. Klimke, “Weierstrass function’s matlab code”, http://matlabdb.mathematik.uni-stuttgart.de/download.jsp?MC_ID=9&MP_ID=56
3. H‑P. Schwefel, “Evolution and Optimum Seeking”, http://ls11‑www.cs.uni-dortmund.de/lehre/wiley/
4. D. Whitley, K. Mathias, S. Rana and J. Dzubera, “Evaluating Evolutionary Algorithms” Artificial Intelligence, 85 (1‑2): 245‑276 AUG 1996.