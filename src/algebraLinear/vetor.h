#ifndef VETOR_H
#define VETOR_H

class Vetor {
public: 
    union {
      double v[4];
      struct {
        double x, y, z, w;
      };
      struct {
        double r, g, b, a;
      };
    };
        
    Vetor();

    Vetor(double x, double y, double z, double w);

    void set(double x, double y, double z, double w);

};

#endif
