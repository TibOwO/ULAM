#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
ofstream ofs;

vector<unsigned> generePremierPlusPetitQue(const unsigned &N)
{
    vector<unsigned> NbrPremier;
    NbrPremier.push_back(1);
    for (unsigned i = 2; i < N; ++i)
    {
        bool isPremier = true;
        for (unsigned j = i - 1; j >= 2; --j)
        {
            unsigned resultat = i % j;
            cout << i << "%" << j << " = " << resultat << endl;
            if (resultat == 0)
            {
                isPremier = false;
                break;
            }
        }
        if (isPremier)
            NbrPremier.push_back(i);
    }
    return NbrPremier;
}

vector<size_t> generePremierPlusPetitQueV2(const size_t &n)
{
    // voir les spec du programmme
    if (n < 2)
        exit(-1);
    // on genère tous les nombres entre [2; n)
    // on mets tous les nombres dans le tableau vectNbPremier
    vector<size_t> vectNbPremier(n - 2);
    for (size_t i(0); i < vectNbPremier.size(); ++i)
        vectNbPremier[i] = i + 2;
    // pour chaque nombre possible
    for (size_t i(0); i < vectNbPremier.size(); ++i)
    {
        // on supprime tous les multiples de i
        if (0 == vectNbPremier[i])
            continue;
        for (size_t j(vectNbPremier[i] * vectNbPremier[i] - 2); j < vectNbPremier.size(); j += vectNbPremier[i])
        {
            vectNbPremier[j] = 0;
        }
    }
    // on supprime tous les 0 -- tassement // ne pas utiliser .erase()
    size_t posAInserer(0);
    for (size_t i(0); i < vectNbPremier.size(); ++i)
    {
        if (vectNbPremier[i] == 0)
            continue;
        vectNbPremier[posAInserer++] = vectNbPremier[i];
    }
    vectNbPremier.resize(posAInserer);
    return vectNbPremier;
}
void affiche(vector<vector<unsigned>> mat)
{
    for (unsigned i = 0; i < mat.size(); i += 1)
    {
        for (unsigned j = 0; j < mat[i].size(); j += 1)
        {
            cout << mat[i][j] << '\t';
        }
        cout << endl;
    }
}

void genereMatricEscargot(vector<vector<unsigned>> &mat, const unsigned &N)
{
    mat.resize(N);
    for (unsigned i = 0; i < mat.size(); ++i)
        mat[i].resize(N, 0);
    unsigned mid = 0;
    if (N / 2 == 0)
    {
        cerr << "Mets un nombre impair bouffon";
        exit(-1);
    }
    else
    {
        mid = (N / 2);
        mat[mid][mid] = 1;
    }
    unsigned y = mid;
    unsigned x = mid;
    unsigned nbr = 2;
    unsigned dec = 1;
    x += 1;
    mat[y][x] = nbr;
    nbr += 1;
    for (; nbr < N * N;)
    {
        for (unsigned haut = 0; haut < dec; haut++)
        {
            y -= 1;
            mat[y][x] = nbr;
            nbr += 1;
        }
        dec += 1;
        for (unsigned gauche = 0; gauche < dec; gauche++)
        {
            x -= 1;
            mat[y][x] = nbr;
            nbr += 1;
        }
        for (unsigned bas = 0; bas < dec; bas++)
        {
            y += 1;
            mat[y][x] = nbr;
            nbr += 1;
        }
        dec += 1;
        for (unsigned droite = 0; droite < dec; droite += 1)
        {
            x += 1;
            mat[y][x] = nbr;
            nbr += 1;
            if (nbr == N * N + 1)
                break;
        }
    }
}

void genereMatricUlam(vector<vector<unsigned>> &mat, const vector<size_t> &nombresPremiers)
{
    for (unsigned i = 0; i < mat.size(); ++i)
    {
        for (unsigned j = 0; j < mat[i].size(); j += 1)
        {
            bool isPremier = false;
            for (unsigned k = 0; k < nombresPremiers.size(); k += 1)
            {
                if (nombresPremiers[k] == mat[i][j])
                {
                    isPremier = true;
                    cout << mat[i][j] << endl;
                    continue;
                }
            }
            if (isPremier == false)
            {
                mat[i][j] = 0;
            }
        }
    }
}

void matriceULAMVersPPM(const vector<vector<unsigned>> &mat, const string &nomFichier)
{
    int couleurR;
    int couleurG;
    int couleurB;
    srand(time(NULL));
    ofs.open(nomFichier);
    ofs << "P3" << endl;
    ofs << mat[0].size() << " " << mat.size() << endl
        << "255" << endl;
    for (unsigned i = 0; i < mat.size(); ++i)
    {
        for (unsigned j = 0; j < mat[i].size(); j += 1)
        {
            couleurR = rand() % 255;
            string stringCouleurR = to_string(couleurR);

            couleurG = rand() % 255;
            string stringCouleurG = to_string(couleurG);

            couleurB = rand() % 255;
            string stringCouleurB = to_string(couleurB);

            if (mat[i][j] == 0)
            {
                ofs << "0 0 0" << endl;
            }
            else
            {
                ofs << stringCouleurR << " " << stringCouleurG << " " << stringCouleurB << endl;
            }
        }
    }
}

int main()
{
    vector<vector<unsigned>> mat;
    cout << "Calcul de tous les nombres premiers necessaire ..." << endl;
    vector<size_t> nbrPrem = generePremierPlusPetitQueV2(1000000);
    cout << "Generation de la matrice escargot (nombres)" << endl;
    genereMatricEscargot(mat, 499);
    cout << "Generation de la matrice Ulam" << endl;
    genereMatricUlam(mat, nbrPrem);
    cout << "Traduction Ulam vers PPM" << endl;
    matriceULAMVersPPM(mat, "CACABis.ppm");
    cout << "Termine !" << endl;
    return 0;
}
