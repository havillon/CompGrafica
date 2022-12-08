#pragma once

class Canvas {

private:
    int wJanela;
    int hJanela;
    int nLinhas;
    int nColunas;

public: 
    Canvas();
    Canvas(int wJanela, int hJanela, int nLinhas, int nColunas);

    int getWJanela();
    void setWJanela(int wJanela);

    int getHJanela();
    void setHJanela(int hJanela);

    int getNLinhas();
    void setNLinhas(int nLinhas);
    
    int getNColunas();
    void setNColunas(int nColunas);
};