
#include "Coordinate.h"
 

namespace yiEngine
{
namespace dateTime
{

/// <summary>
/// �¶�����ʱʹ�õ�����(?)
/// </summary>
static double nutB[] = 
{
    2.1824,  -33.75705, 36e-6,-1720,920,
    3.5069, 1256.66393, 11e-6,-132, 57,
    1.3375,16799.4182, -51e-6, -23, 10,
    4.3649,  -67.5141,  72e-6,  21, -9,
    0.04,   -628.302,   0,     -14,  0,
    2.36,   8328.691,   0,       7,  0,
    3.46,   1884.966,   0,      -5,  2,
    5.44,  16833.175,   0,      -4,  2,
    3.69,  25128.110,   0,      -3,  0,
    3.55,    628.362,   0,       2,  0
};


/// <summary>
/// ����������ת
/// </summary>
/// <param name="JW"></param>
/// <param name="E"></param>
void Coordinate::llrConv(double JW[], double E)
{
    //�Ƶ��������任,�ൽ��Eȡ��
    double sinE = sin(E), cosE = cos(E);
    double sinJ = sin(JW[0]), cosJ = cos(JW[0]);
    double sinW = sin(JW[1]), cosW = cos(JW[1]), tanW = tan(JW[1]);
    JW[0] = atan2(sinJ * cosE - tanW * sinE, cosJ);
    JW[1] = asin(cosE * sinW + sinE * cosW * sinJ);
    JW[0] = commonDef::rad2mrad(JW[0]);
}

#if 0
/// <summary>
/// ����������ת
/// </summary>
/// <param name="JW"></param>
/// <param name="E"></param>
void llrConv(double JW[], double E)  
{
    //�Ƶ��������任,�ൽ��Eȡ��
    double sinE = sin(E), cosE = cos(E);
    double sinJ = sin((JW[0])), cosJ = cos((JW[0]));
    double sinW = sin((JW[1]));
    double cosW = cos((JW[1]));
    double tanW = tan((JW[1]));
    JW[0] = atan2(sinJ * cosE - tanW * sinE, cosJ);
    JW[1] = asin(cosE * sinW + sinE * cosW * sinJ);
    JW[0] = commonDef::rad2mrad((JW[0]));
}
#endif


/// <summary>
/// ����תֱ������
/// </summary>
/// <param name="J"></param>
/// <param name="W"></param>
/// <param name="R"></param>
/// <param name="z"></param>
void Coordinate::llr2xyz(double J, double W, double R, double z[])
{
    z[0] = R * cos(W) * cos(J);
    z[1] = R * cos(W) * sin(J);
    z[2] = R * sin(W);
}

/// <summary>
/// ֱ������ת��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="q"></param>
void Coordinate::xyz2llr(double x, double y, double z, double q[])
{ 
    q[2] = sqrt(x * x + y * y + z * z);
    q[1] = asin(z / q[2]);
    q[0] = commonDef::rad2mrad(atan2(y, x));
}

/// <summary>
/// �¶�(�ƾ��¶��ͽ����¶�)����,t��������
/// </summary>
/// <param name="t">������</param>
void Coordinate::nutation(double t)
{ 
    int i;
    double c, a, t2 = t * t;
    double tdL = 0; 
    double tdE = 0;
    double* B = nutB;
    for (i = 0; i < 50; i += 5)
    {
        c = B[i] + B[i + 1] * t + B[i + 2] * t2;
        
        if (i == 0) 
            a = -1.742 * t; 
        else 
            a = 0;

        tdL += (B[i + 3] + a) * sin(c);
        tdE += B[i + 4] * cos(c);
    }
    dL = tdL / 100 / commonDef::RAD;  //�ƾ��¶�
    dE = tdE / 100 / commonDef::RAD;  //�����¶�
}


/// <summary>
/// ֻ����ƾ��¶�
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
double Coordinate::nutationLon(double t)
{ 
    int i;
    double a, t2 = t * t, dL = 0;
    double* B = nutB;
    for (i = 0; i < 49; i += 5)
    {
        if (i == 0) a = -1.742 * t; else a = 0;
        dL += (B[i + 3] + a) * sin(B[i] + B[i + 1] * t + B[i + 2] * t2);
    }
    return dL / 100 / commonDef::RAD;
}

/// <summary>
/// ���ػƳཻ��,t��������
/// </summary>
/// <param name="t">������</param>
/// <returns></returns>
double Coordinate::hcjj(double t)
{
    double t2 = t * t, t3 = t2 * t, t4 = t3 * t;
    return (84381.4088 - 46.836051 * t - 0.0001667 * t2 - 0.00199911 * t3 - 0.000000523 * t4) / commonDef::RAD;
}



/// <summary>
/// ��ǶȲ�(δ����)
/// </summary>
/// <param name="J1"></param>
/// <param name="W1"></param>
/// <param name="J2"></param>
/// <param name="W2"></param>
/// <returns></returns>
double Coordinate::j1_j2(double J1, double W1, double J2, double W2)
{
    double dJ = commonDef::rad2rrad(J1 - J2), dW = W1 - W2;
    if (abs(dJ) < 1 / 1000 && abs(dW) < 1 / 1000)
    {
        dJ *= cos((W1 + W2) / 2);
        return sqrt(dJ * dJ + dW * dW);
    }
    return acos(sin(W1) * sin(W2) + cos(W1) * cos(W2) * cos(dJ));
}


/// <summary>
/// ����T��2000�������������(UT),dt��deltatT(��),����Ҫ�󲻸�ʱdt��ȡֵΪ0
/// ���ظ������κ���ʱ(�����ྭ�¶����Ƕ���ʽ����),��������������Ȧ��ƽ���������ĳྭ
/// </summary>
/// <param name="T">2000�������������(UT)</param>
/// <param name="dt">deltatT(��)</param>
/// <returns></returns>
double Coordinate::gst(double T, double dt)
{
    double t = (T + dt) / 36525, t2 = t * t, t3 = t2 * t, t4 = t3 * t;
    return commonDef::pi2 * (0.7790572732640 + 1.00273781191135448 * T) //�ϸ�˵�����T��UT,��һ�е�t����ѧʱ(������)
        + (0.014506 + 4612.15739966 * t + 1.39667721 * t2 - 0.00009344 * t3 + 0.00001882 * t4) / commonDef::RAD;
}


/// <summary>
/// ̫�����в�,t��������
/// </summary>
/// <param name="t">������</param>
/// <returns></returns>
double Coordinate::gxc_sunLon(double t)
{
    double v = -0.043126 + 628.301955 * t - 0.000002732 * t * t; //ƽ�����
    double e = 0.016708634 - 0.000042037 * t - 0.0000001267 * t * t;
    return (-20.49552 * (1 + e * cos(v))) / commonDef::RAD; //�ƾ����в�
}

/// <summary>
/// ��γ���в�
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
double Coordinate::gxc_sunLat(double t)
{
    return 0;
}

/// <summary>
/// ���򾭶ȹ��в�,���0.07"
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
double Coordinate::gxc_moonLon(double t)
{
    return -3.4E-6;
}

/// <summary>
/// ����γ�ȹ��в�,���0.006"
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
double Coordinate::gxc_moonLat(double t)
{
    return 0.063 * sin(0.057 + 8433.4662 * t + 0.000064 * t * t) / commonDef::RAD;
}

/// <summary>
/// ��������,ho���Ӹ߶�
/// </summary>
/// <param name="ho"></param>
/// <returns></returns>
double Coordinate::AR(double ho)
{
    return -0.0002909 / tan(ho + 0.002227 / (ho + 0.07679));
}


/// <summary>
/// ��������,h����߶�
/// </summary>
/// <param name="h"></param>
/// <returns></returns>
double Coordinate::AR2(double h)
{
    return 0.0002967 / tan(h + 0.003138 / (h + 0.08919));
}

/// <summary>
/// �Ӳ�����
/// </summary>
/// <param name="z">�������</param>
/// <param name="H">ʱ��</param>
/// <param name="fa">����γ��</param>
/// <param name="high">����(ǧ��)</param>
void Coordinate::parallax(double z[], double H, double fa, double high)
{
    double dw = 1.0;
    if (z[2] < 500) dw = cs_AU;
    z[2] *= dw;
    double r0, x0, y0, z0, f = 0.99664719;
    double u = atan(f * tan(fa));
    double g = z[0] + H;
    r0 = cs_rEar * cos(u) + high * cos(fa); //վ����ص����򾶵ĳ��ͶӰ����
    z0 = cs_rEar * sin(u) * f + high * sin(fa); //վ����ص����򾶵�����ͶӰ����
    x0 = r0 * cos(g);
    y0 = r0 * sin(g);

    llr2xyz(z[0], z[1], z[2], z);
    z[0] -= x0; z[1] -= y0; z[2] -= z0;
    xyz2llr(z[0], z[1], z[2], z);
    z[2] /= dw;
}

/// <summary>
/// ��ռ��������������Ľ���(������1�Ľ���),������ZB.le_J,le_W,������ꡣR1,R2��λ��ǧ��
/// </summary>
/// <param name="J1"></param>
/// <param name="W1"></param>
/// <param name="R1"></param>
/// <param name="J2"></param>
/// <param name="W2"></param>
/// <param name="R2"></param>
void Coordinate::line_earth(double J1, double W1, double R1, double J2, double W2, double R2)
{
    double x1 = R1 * cos(W1) * cos(J1), y1 = R1 * cos(W1) * sin(J1), z1 = R1 * sin(W1);
    double x2 = R2 * cos(W2) * cos(J2), y2 = R2 * cos(W2) * sin(J2), z2 = R2 * sin(W2);
    double dx = x2 - x1, dy = y2 - y1, dz = z2 - z1, f = 0.99664719, r = cs_rEar; //ֱ�߲������������
    double x, y, z, lh = 0;
    if (abs(dx) < abs(dy)) //��Ҫʱ�ػ�
    { lh = dx; dx = dy; dy = lh; lh = x1; x1 = y1; y1 = lh; lh = 1; }
    double a = dy / dx, b = y1 - a * x1, c = dz / dx / f, d = z1 / f - c * x1;
    double A = a * a + c * c + 1, B = a * b + c * d, C = b * b + d * d - r * r, D = B * B - A * C;
    if (D < 0) { le_J = le_W = 100; return; } //����100��ʾ�޽�
    D = sqrt(D); if (x1 + B / A < 0) D = -D;
    x = (-B + D) / A; y = a * x + b; z = (c * x + d) / f;
    le_R1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1) + (z - z1) * (z - z1));
    if (lh != 0) { lh = x; x = y; y = lh; }
    le_W = atan(z / sqrt(x * x + y * y));
    le_J = commonDef::rad2mrad(atan2(y, x));
}

}  // namespace dateTime
}  // namespace YiEngine