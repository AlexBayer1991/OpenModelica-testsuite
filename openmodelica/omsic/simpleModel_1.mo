model simpleModel_1
    Real x(start=1);
    Real y(start=1);
    parameter Real a=0.9, b=1;
  equation
    der(x)=a*x+sin(x*time);
    der(y)=b*y;
end simpleModel_1;