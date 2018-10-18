model simpleLoop
    Real x(start=1);
    Real y(start=2);
	Real z(start=3);
    parameter Real a=1, b=-1;
  equation
    time = a*x+b*y;
    cos(time) = 2*a*x+sin(y);
	der(z) = x+y;
end simpleLoop;