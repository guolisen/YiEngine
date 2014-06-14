

#include "TimeInfo.h"


namespace yiEngine
{
namespace dateTime
{




/// <summary>
/// ���� sun_moon ��ĳ�Ա��������T����ѧʱ,վ�㾭��longitude,γ��latitude,����high(ǧ��)
/// </summary>
/// <param name="T">��ѧʱ</param>
/// <param name="longitude">վ�㾭��</param>
/// <param name="latitude">վ��γ��</param>
/// <param name="high">����</param>
TimeInfo TimeCalculator::Calculator(double rawTimeTick, double longitude, double latitude, double high)
{
    double T =  (rawTimeTick * 1000.0) / 86400000.0 - 10957.5;
    T += julianDay_.deltatT2(T);

    //������������
    timeInfo_.T = T; 
    timeInfo_.longitude = longitude; 
    timeInfo_.latitude  = latitude;
    timeInfo_.dt = julianDay_.deltatT2(T); //TD-UT
    timeInfo_.jd = T - timeInfo_.dt;    //UT
    T /= 36525; coordinate_.nutation(T);
    timeInfo_.dL = coordinate_.dL;   //�ƾ���
    timeInfo_.dE = coordinate_.dE;   //�����¶�
    timeInfo_.E = coordinate_.hcjj(T) + timeInfo_.dE; //��Ƴཻ��
    timeInfo_.gst = coordinate_.gst(timeInfo_.jd, timeInfo_.dt) + timeInfo_.dL * cos(timeInfo_.E); //�����ʱ(�����ǷǶ���ʽ����)
    double z[4] = {0};

    //=======����========
    //�����Ƶ�����
    starCalendar_.M_coord(T, z, -1.0, -1.0, -1.0); //��������
    z[0] = commonDef::rad2mrad(z[0] + coordinate_.gxc_moonLon(T) + timeInfo_.dL); z[1] += coordinate_.gxc_moonLat(T);  //����������в�¶�
    timeInfo_.mHJ = z[0]; timeInfo_.mHW = z[1]; timeInfo_.mR = z[2]; //�����ӻƾ�,�ӻ�γ,�������ľ�

    //����������
    coordinate_.llrConv(z, timeInfo_.E); //תΪ�������
    timeInfo_.mCJ = z[0]; timeInfo_.mCW = z[1]; //�����ӳྭ,�����γ

    //����ʱ�Ǽ���
    timeInfo_.mShiJ = commonDef::rad2mrad(timeInfo_.gst - longitude - z[0]); //�õ��˿�����ʱ��
    if (timeInfo_.mShiJ > M_PI) timeInfo_.mShiJ -= commonDef::pi2;

    //�������Ӳ�ĳ������
    coordinate_.parallax(z, timeInfo_.mShiJ, latitude, high); //�Ӳ�����
    timeInfo_.mCJ2 = z[0]; timeInfo_.mCW2 = z[1]; timeInfo_.mR2 = z[2];

    //����ʱ������
    z[0] += M_PI / 2.0 - timeInfo_.gst + longitude;  //ת������ڵ�ƽ����ֵ�ĳ������(ʱ������)

    //������ƽ����
    coordinate_.llrConv(z, M_PI / 2.0 - latitude);    //ת����ƽ����(ֻ�ľ�γ��)
    z[0] = commonDef::rad2mrad(M_PI / 2.0 - z[0]);
    timeInfo_.mDJ = z[0]; timeInfo_.mDW = z[1]; //��λ��,�߶Ƚ�
    if (z[1] > 0) z[1] += coordinate_.AR2(z[1]); //������������
    timeInfo_.mPJ = z[0]; timeInfo_.mPW = z[1]; //��λ��,�߶Ƚ�

    //=======̫��========
    //̫���Ƶ�����
    starCalendar_.E_coord(T, z, -1, -1, -1);   //��������
    z[0] = commonDef::rad2mrad(z[0] + M_PI + coordinate_.gxc_sunLon(T) + timeInfo_.dL);  //����̫�����в�¶�
    z[1] = -z[1] + coordinate_.gxc_sunLat(T); //z����Ϊ̫�����ĻƵ�������
    timeInfo_.sHJ = z[0]; timeInfo_.sHW = z[1]; timeInfo_.sR = z[2]; //̫���ӻƾ�,�ӻ�γ,�յ����ľ�

    //̫���������
    coordinate_.llrConv(z, timeInfo_.E); //תΪ�������
    timeInfo_.sCJ = z[0]; timeInfo_.sCW = z[1]; //̫���ӳྭ,�ӳ�γ

    //̫��ʱ�Ǽ���
    timeInfo_.sShiJ = commonDef::rad2mrad(timeInfo_.gst - longitude - z[0]); //�õ��˿�����ʱ��
    if (timeInfo_.sShiJ > M_PI) timeInfo_.sShiJ -= commonDef::pi2;

    //�������Ӳ�ĳ������
    coordinate_.parallax(z, timeInfo_.sShiJ, latitude, high); //�Ӳ�����
    timeInfo_.sCJ2 = z[0]; timeInfo_.sCW2 = z[1]; timeInfo_.sR2 = z[2];

    //̫��ʱ������
    z[0] += M_PI / 2.0 - timeInfo_.gst + longitude;  //ת������ڵ�ƽ����ֵ�ĳ������

    //̫����ƽ����
    coordinate_.llrConv(z, M_PI / 2.0 - latitude);
    z[0] = commonDef::rad2mrad(M_PI / 2.0 - z[0]);
    //z[1] -= 8.794/rad/z[2]*Math.cos(z[1]); //ֱ���ڵ�ƽ�������Ӳ�����(����ѵ���Ϊ����,���ȱ�coordinate_.parallax()�Բ�һЩ)
    timeInfo_.sDJ = z[0]; timeInfo_.sDW = z[1]; //��λ��,�߶Ƚ�

    if (z[1] > 0) z[1] += coordinate_.AR2(z[1]); //������������
    timeInfo_.sPJ = z[0]; timeInfo_.sPW = z[1]; //��λ��,�߶Ƚ�

    //=======����========
    //ʱ�����
    double t = T / 10; double t2 = t * t, t3 = t2 * t, t4 = t3 * t, t5 = t4 * t;
    double Lon = (1753469512.0 + 6283319653318.0 * t + 529674.0 * t2 + 432.0 * t3 - 1124.0 * t4 - 9.0 * t5 + 630.0 * cos(6.0 + 3.0 * t)) / 1000000000.0 + M_PI - 20.5 / commonDef::RAD; //�����˹��в��̫��ƽ�ƾ�
    Lon = commonDef::rad2mrad(Lon - (timeInfo_.sCJ - timeInfo_.dL * cos(timeInfo_.E))); //(�����˹��в��ƽ�ƾ�)-(����dL*cos(E)���ӳྭ)
    if (Lon > M_PI) Lon -= commonDef::pi2; //�õ�ʱ��,��λ�ǻ���
    timeInfo_.sc = Lon / commonDef::pi2;   //ʱ��(��λ:��)

    //��̫����ƽ̫��
    timeInfo_.pty = timeInfo_.jd - longitude / commonDef::pi2;  //ƽ̫��ʱ
    timeInfo_.zty = timeInfo_.jd - longitude / commonDef::pi2 + timeInfo_.sc; //��̫��ʱ

    //�Ӱ뾶
    //timeInfo_.mRad = starCalendar_.moonRad(timeInfo_.mR,timeInfo_.mDW);  //�����Ӱ뾶(����)
    timeInfo_.mRad = 358473400.0 / timeInfo_.mR2; //�����Ӱ뾶(����)
    timeInfo_.sRad = 959.63 / timeInfo_.sR2; //̫���Ӱ뾶(����)
    timeInfo_.e_mRad = 358473400.0 / timeInfo_.mR; //���������Ӱ뾶(����)
    timeInfo_.eShadow = (commonDef::cs_rEarA / timeInfo_.mR * commonDef::RAD - (959.63 - 8.794) / timeInfo_.sR) * 51.0 / 50.0; //�ر�Ӱ�������򾶴��İ뾶(����),ʽ��51/50�Ǵ�����Ȳ���
    timeInfo_.eShadow2 = (commonDef::cs_rEarA / timeInfo_.mR * commonDef::RAD + (959.63 + 8.794) / timeInfo_.sR) * 51.0 / 50.0; //�ذ�Ӱ�������򾶴��İ뾶(����),ʽ��51/50�Ǵ�����Ȳ���
    timeInfo_.mIll = starCalendar_.moonIll(T); //�������������

    //����ʳ����
    if (abs(commonDef::rad2rrad(timeInfo_.mCJ - timeInfo_.sCJ)) < 50 / 180 * M_PI)
    {
        coordinate_.line_earth(timeInfo_.mCJ, timeInfo_.mCW, timeInfo_.mR, timeInfo_.sCJ, timeInfo_.sCW, timeInfo_.sR * commonDef::cs_AU);
        timeInfo_.zx_J = commonDef::rad2rrad(timeInfo_.gst - coordinate_.le_J);
        timeInfo_.zx_W = coordinate_.le_W; //�޽ⷵ��ֵ��100
    }
    else 
        timeInfo_.zx_J = timeInfo_.zx_W = 100;

    return timeInfo_;
}


}  // namespace dateTime
}  // namespace YiEngine
