model simpleLoop
    Real x(start=131/6);
    Real y(start=-2227/24);
    Real z(start=-131/8);
    Real s(start=1, fixed=true);
    parameter Real a=1, b=-1, c = 7;
  equation
    time = a*x+b*y+c*z;
    2*time = 2*a*x+y-3*z;
    7 = 23*a-3/8*b+z;
    der(s) = x+y+z;
end simpleLoop;
