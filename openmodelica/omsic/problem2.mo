model problem2 "simple linear torn system"
Real u1(start=1), u2(start=1), u3(start=1);
Real v1(start=-0.1, fixed=true);
Real w1(start=0.1, fixed=true);
Real p1 = 0.5;
parameter Integer p2 = 7;
equation

// simple linear loop
 u1 + 5*u2 + u3 = 0.5;
-u1 +   u2 - u3 = 10*v1;
 u1 + 3*u2 - u3 = -0.1;

der(v1) = v1*p1*p2 "simple ODE";

der(w1) = sin(w1*p1) "simple ODE";

end problem2;
