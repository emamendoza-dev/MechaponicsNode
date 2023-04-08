// Number of inputs to the fuzzy inference system
const int fis_gcI = 2;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 3;
// Number of rules to the fuzzy inference system
const int fis_gcR = 25;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

//***********************************************************************
// Support functions for Fuzzy Inference System                          
//***********************************************************************
// Trapezoidal Member Function
FIS_TYPE fis_trapmf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2], d = p[3];
    FIS_TYPE t1 = ((x <= c) ? 1 : ((d < x) ? 0 : ((c != d) ? ((d - x) / (d - c)) : 0)));
    FIS_TYPE t2 = ((b <= x) ? 1 : ((x < a) ? 0 : ((a != b) ? ((x - a) / (b - a)) : 0)));
    return (FIS_TYPE) min(t1, t2);
}

// Triangular Member Function
FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2];
    FIS_TYPE t1 = (x - a) / (b - a);
    FIS_TYPE t2 = (c - x) / (c - b);
    if ((a == b) && (b == c)) return (FIS_TYPE) (x == a);
    if (a == b) return (FIS_TYPE) (t2*(b <= x)*(x <= c));
    if (b == c) return (FIS_TYPE) (t1*(a <= x)*(x <= b));
    t1 = min(t1, t2);
    return (FIS_TYPE) max(t1, 0.0f);
}

FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b)
{
    return min(a, b);
}

FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b)
{
    return max(a, b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp)
{
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++)
    {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}


//***********************************************************************
// Data for Fuzzy Inference System                                       
//***********************************************************************
// Pointers to the implementations of member functions
_FIS_MF fis_gMF[] =
{
    fis_trapmf, fis_trimf
};

// Count of member function for each Input
int fis_gIMFCount[] = { 5, 5 };

// Count of member function for each Output 
int fis_gOMFCount[] = { 3, 3, 3 };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFI0Coeff1[] = { -1, -1, -0.8, -0.6 };
FIS_TYPE fis_gMFI0Coeff2[] = { -0.7, -0.4, -0.15 };
FIS_TYPE fis_gMFI0Coeff3[] = { -0.2, 0, 0.2 };
FIS_TYPE fis_gMFI0Coeff4[] = { 0.15, 0.4, 0.7 };
FIS_TYPE fis_gMFI0Coeff5[] = { 0.6, 0.8, 1, 1 };
FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2, fis_gMFI0Coeff3, fis_gMFI0Coeff4, fis_gMFI0Coeff5 };
FIS_TYPE fis_gMFI1Coeff1[] = { -100, -100, -60 };
FIS_TYPE fis_gMFI1Coeff2[] = { -70, -50, -20 };
FIS_TYPE fis_gMFI1Coeff3[] = { -30, 0, 30 };
FIS_TYPE fis_gMFI1Coeff4[] = { 20, 50, 70 };
FIS_TYPE fis_gMFI1Coeff5[] = { 60, 100, 100 };
FIS_TYPE* fis_gMFI1Coeff[] = { fis_gMFI1Coeff1, fis_gMFI1Coeff2, fis_gMFI1Coeff3, fis_gMFI1Coeff4, fis_gMFI1Coeff5 };
FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff, fis_gMFI1Coeff };

// Coefficients for the Output Member Functions
FIS_TYPE fis_gMFO0Coeff1[] = { 0, 0, 0.05 };
FIS_TYPE fis_gMFO0Coeff2[] = { 0.04, 0.25, 0.35 };
FIS_TYPE fis_gMFO0Coeff3[] = { 0.25, 0.4, 0.5, 0.5 };
FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3 };
FIS_TYPE fis_gMFO1Coeff1[] = { 0, 0, 0.05 };
FIS_TYPE fis_gMFO1Coeff2[] = { 0.04, 0.25, 0.35 };
FIS_TYPE fis_gMFO1Coeff3[] = { 0.25, 0.4, 0.5, 0.5 };
FIS_TYPE* fis_gMFO1Coeff[] = { fis_gMFO1Coeff1, fis_gMFO1Coeff2, fis_gMFO1Coeff3 };
FIS_TYPE fis_gMFO2Coeff1[] = { 0, 0, 0.15 };
FIS_TYPE fis_gMFO2Coeff2[] = { 0.1, 1, 1.5 };
FIS_TYPE fis_gMFO2Coeff3[] = { 1, 1.5, 2, 2 };
FIS_TYPE* fis_gMFO2Coeff[] = { fis_gMFO2Coeff1, fis_gMFO2Coeff2, fis_gMFO2Coeff3 };
FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff, fis_gMFO1Coeff, fis_gMFO2Coeff };

// Input membership function set
int fis_gMFI0[] = { 0, 1, 1, 1, 0 };
int fis_gMFI1[] = { 1, 1, 1, 1, 1 };
int* fis_gMFI[] = { fis_gMFI0, fis_gMFI1};

// Output membership function set
int fis_gMFO0[] = { 1, 1, 0 };
int fis_gMFO1[] = { 1, 1, 0 };
int fis_gMFO2[] = { 1, 1, 0 };
int* fis_gMFO[] = { fis_gMFO0, fis_gMFO1, fis_gMFO2};

// Rule Weights
FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Type
int fis_gRType[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Inputs
int fis_gRI0[] = { 1, 1 };
int fis_gRI1[] = { 2, 1 };
int fis_gRI2[] = { 3, 1 };
int fis_gRI3[] = { 4, 1 };
int fis_gRI4[] = { 5, 1 };
int fis_gRI5[] = { 1, 2 };
int fis_gRI6[] = { 2, 2 };
int fis_gRI7[] = { 3, 2 };
int fis_gRI8[] = { 4, 2 };
int fis_gRI9[] = { 5, 2 };
int fis_gRI10[] = { 1, 3 };
int fis_gRI11[] = { 2, 3 };
int fis_gRI12[] = { 3, 3 };
int fis_gRI13[] = { 4, 3 };
int fis_gRI14[] = { 5, 3 };
int fis_gRI15[] = { 1, 4 };
int fis_gRI16[] = { 2, 4 };
int fis_gRI17[] = { 3, 4 };
int fis_gRI18[] = { 4, 4 };
int fis_gRI19[] = { 5, 4 };
int fis_gRI20[] = { 1, 5 };
int fis_gRI21[] = { 2, 5 };
int fis_gRI22[] = { 3, 5 };
int fis_gRI23[] = { 4, 5 };
int fis_gRI24[] = { 5, 5 };
int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7, fis_gRI8, fis_gRI9, fis_gRI10, fis_gRI11, fis_gRI12, fis_gRI13, fis_gRI14, fis_gRI15, fis_gRI16, fis_gRI17, fis_gRI18, fis_gRI19, fis_gRI20, fis_gRI21, fis_gRI22, fis_gRI23, fis_gRI24 };

// Rule Outputs
int fis_gRO0[] = { 3, 1, 1 };
int fis_gRO1[] = { 2, 1, 1 };
int fis_gRO2[] = { 1, 1, 1 };
int fis_gRO3[] = { 1, 2, 1 };
int fis_gRO4[] = { 1, 3, 1 };
int fis_gRO5[] = { 3, 1, 1 };
int fis_gRO6[] = { 2, 1, 1 };
int fis_gRO7[] = { 1, 1, 1 };
int fis_gRO8[] = { 1, 2, 1 };
int fis_gRO9[] = { 1, 3, 1 };
int fis_gRO10[] = { 3, 1, 1 };
int fis_gRO11[] = { 2, 1, 1 };
int fis_gRO12[] = { 1, 1, 1 };
int fis_gRO13[] = { 1, 2, 1 };
int fis_gRO14[] = { 3, 1, 1 };
int fis_gRO15[] = { 3, 1, 2 };
int fis_gRO16[] = { 2, 1, 2 };
int fis_gRO17[] = { 1, 1, 2 };
int fis_gRO18[] = { 1, 2, 2 };
int fis_gRO19[] = { 1, 3, 2 };
int fis_gRO20[] = { 3, 1, 3 };
int fis_gRO21[] = { 2, 1, 3 };
int fis_gRO22[] = { 2, 1, 3 };
int fis_gRO23[] = { 1, 1, 3 };
int fis_gRO24[] = { 1, 3, 3 };
int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7, fis_gRO8, fis_gRO9, fis_gRO10, fis_gRO11, fis_gRO12, fis_gRO13, fis_gRO14, fis_gRO15, fis_gRO16, fis_gRO17, fis_gRO18, fis_gRO19, fis_gRO20, fis_gRO21, fis_gRO22, fis_gRO23, fis_gRO24 };

// Input range Min
FIS_TYPE fis_gIMin[] = { -1, -100 };

// Input range Max
FIS_TYPE fis_gIMax[] = { 1, 100 };

// Output range Min
FIS_TYPE fis_gOMin[] = { 0, 0, 0 };

// Output range Max
FIS_TYPE fis_gOMax[] = { 0.5, 0.5, 2 };

//***********************************************************************
// Data dependent support functions for Fuzzy Inference System           
//***********************************************************************
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o)
{
    FIS_TYPE mfOut;
    int r;

    for (r = 0; r < fis_gcR; ++r)
    {
        int index = fis_gRO[r][o];
        if (index > 0)
        {
            index = index - 1;
            mfOut = (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else if (index < 0)
        {
            index = -index - 1;
            mfOut = 1 - (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else
        {
            mfOut = 0;
        }

        fuzzyRuleSet[0][r] = fis_min(mfOut, fuzzyRuleSet[1][r]);
    }
    return fis_array_operation(fuzzyRuleSet[0], fis_gcR, fis_max);
}

FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o)
{
    FIS_TYPE step = (fis_gOMax[o] - fis_gOMin[o]) / (FIS_RESOLUSION - 1);
    FIS_TYPE area = 0;
    FIS_TYPE momentum = 0;
    FIS_TYPE dist, slice;
    int i;

    // calculate the area under the curve formed by the MF outputs
    for (i = 0; i < FIS_RESOLUSION; ++i){
        dist = fis_gOMin[o] + (step * i);
        slice = step * fis_MF_out(fuzzyRuleSet, dist, o);
        area += slice;
        momentum += slice*dist;
    }

    return ((area == 0) ? ((fis_gOMax[o] + fis_gOMin[o]) / 2) : (momentum / area));
}

//***********************************************************************
// Fuzzy Inference System                                                
//***********************************************************************
void fis_evaluate()
{
    FIS_TYPE fuzzyInput0[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE fuzzyInput1[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE* fuzzyInput[fis_gcI] = { fuzzyInput0, fuzzyInput1, };
    FIS_TYPE fuzzyOutput0[] = { 0, 0, 0 };
    FIS_TYPE fuzzyOutput1[] = { 0, 0, 0 };
    FIS_TYPE fuzzyOutput2[] = { 0, 0, 0 };
    FIS_TYPE* fuzzyOutput[fis_gcO] = { fuzzyOutput0, fuzzyOutput1, fuzzyOutput2, };
    FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
    FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
    FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
    FIS_TYPE sW = 0;

    // Transforming input to fuzzy Input
    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i)
    {
        for (j = 0; j < fis_gIMFCount[i]; ++j)
        {
            fuzzyInput[i][j] =
                (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r)
    {
        if (fis_gRType[r] == 1)
        {
            fuzzyFires[r] = FIS_MAX;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1);
            }
        }
        else
        {
            fuzzyFires[r] = FIS_MIN;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0)
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    }
    else
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = fis_defuzz_centroid(fuzzyRuleSet, o);
        }
    }
}

// ***** NO BORRAR ***** NO BORRAR ***** NO BORRAR ***** NO BORRAR ***** NO BORRAR ***** NO BORRAR ***** NO BORRAR *****

// This function prepares the inputs of the Fuzzy Control
void prepareInputsFuzzyControl(float targetPH, float targetCE, float realPH, float realCE){
    // Calculate error
    g_fisInput[0] = targetPH - realPH; // error pH
    g_fisInput[1] = targetCE - realCE; //error CE

    // Put Inputs at intervals (pH -1 to 1 and CE -100 to 100)
    if(g_fisInput[0] <= -1)
    g_fisInput[0] = -0.99;
    if(g_fisInput[0] >= 1)
    g_fisInput[0] = 0.99;

    if(g_fisInput[1] <= -100)
    g_fisInput[1] = -99;
    if(g_fisInput[1] >= 100)
    g_fisInput[1] = 99;
}

// This function prepares the values obtained by the controller
// Transform the values from s to ms and makes output Zero if the output is small
void prepareOutputsFuzzyControl(int signalOutputAmplifier){
    for(int i=0; i<3; i++){
        g_fisOutput[i] = g_fisOutput[i]*1000*signalOutputAmplifier; // Convert output to ms
    }
    g_fisOutput[2] = g_fisOutput[2]*5; 
    if(g_fisInput[1] < 0 || abs(g_fisInput[1]) <= 30) // If the CE error is negative
    g_fisOutput[2] = 0.0; // Never activate SNM pump

    if(abs(g_fisInput[0]) <= 0.2){
        g_fisOutput[0] = 0.0;
        g_fisOutput[1] = 0.0;
    }
}

// This function prints the final results of Fuzzy Controller
void printFuzzyControlResults(){
    Serial.println("INPUTS");
    Serial.print("pH error: ");
    Serial.println(g_fisInput[0]);
    Serial.print("CE error: ");
    Serial.print(g_fisInput[1]);
    Serial.println("uS/cm");

    Serial.println("OUTPUT");
    Serial.print("ACIDE: ");
    Serial.print(g_fisOutput[0]);
    Serial.println(" ms");
    Serial.print("BASE: ");
    Serial.print(g_fisOutput[1]);
    Serial.println(" ms");
    Serial.print("SNM: ");
    Serial.print(g_fisOutput[2]);
    Serial.println(" ms");
}

// This fuction returns T if pHError || CEError is more than permisible values
bool is_pH_CE_Error(float permisibleErrorpH, float permisibleErrorCE) {
    Serial.print("Error en pH o CE");
    Serial.println(abs(g_fisInput[0]) >= permisibleErrorpH || abs(g_fisInput[1]) >= permisibleErrorCE);
    return (abs(g_fisInput[0]) >= permisibleErrorpH || abs(g_fisInput[1]) >= permisibleErrorCE);
}