model simpleModel_1
    Real x(start=1);
    Real y(start=1);
    Real z(start=1);
    parameter Real a=1, b=1, c=1;
  equation
    der(x)=a*x;
    der(y)=b*y;
    der(z)=c*z;
end simpleModel_1;