model simpleModel_2
    Real x(start=1);
    Real y(start=1);
    Real z(start=1);
    parameter Real a=0.9, b=1, c=1.1;
  equation
    der(x)=a*x;
    der(y)=b*y + x;
    der(z)=c*z*y;
end simpleModel_2;