#include <string>
#include <map>

#include <boost/format.hpp>

#include <YiEngine/DateTime/DateTimeCommonDef.h>
#include "JulianDay.h"
#include "StarCalendar.h"
#include "MoonCalculate.h"

namespace yiEngine
{
namespace dateTime
{

/// <summary>
/// ˷ֱ����ϲ���
/// </summary>
static double suoKBArray[] = 
{ //˷ֱ����ϲ���
    1457698.231017,29.53067166, // -721-12-17 h=0.00032 ����������
    1546082.512234,29.53085106, // -479-12-11 h=0.00053 ������ս��
    1640640.735300,29.53060000, // -221-10-31 h=0.01010 �������غ�
    1642472.151543,29.53085439, // -216-11-04 h=0.00040 �������غ�

    1683430.509300,29.53086148, // -104-12-25 h=0.00313 ���顤����־(̫����)ƽ��ƽ˷
    1752148.041079,29.53085097, //   85-02-13 h=0.00049 ���顤����־(�ķ���)
    1807665.420323,29.53059851, //  237-02-12 h=0.00033 ���顤����־(������)
    1883618.114100,29.53060000, //  445-01-24 h=0.00030 ���顤����־(�γ���Ԫ����)
    1907360.704700,29.53060000, //  510-01-26 h=0.00030 ���顤����־(���֮������)
    1936596.224900,29.53060000, //  590-02-10 h=0.01010 ���顤����־(������)
    1939135.675300,29.53060000, //  597-01-24 h=0.00890 ���顤����־(��ҵ��)
    1947168.00//  619-01-21
};

/// <summary>
/// ��ֱ����ϲ���
/// </summary>
static double qiKBArray[] = 
{ //��ֱ����ϲ���
    1640650.479938,15.21842500, // -221-11-09 h=0.01709 �������غ�
    1642476.703182,15.21874996, // -216-11-09 h=0.01557 �������غ�

    1683430.515601,15.218750011, // -104-12-25 h=0.01560 ���顤����־(̫����)ƽ��ƽ˷ �ع���=365.25000
    1752157.640664,15.218749978, //   85-02-23 h=0.01559 ���顤����־(�ķ���) �ع���=365.25000
    1807675.003759,15.218620279, //  237-02-22 h=0.00010 ���顤����־(������) �ع���=365.24689
    1883627.765182,15.218612292, //  445-02-03 h=0.00026 ���顤����־(�γ���Ԫ����) �ع���=365.24670
    1907369.128100,15.218449176, //  510-02-03 h=0.00027 ���顤����־(���֮������) �ع���=365.24278
    1936603.140413,15.218425000, //  590-02-17 h=0.00149 ���顤����־(������) �ع���=365.24220
    1939145.524180,15.218466998, //  597-02-03 h=0.00121 ���顤����־(��ҵ��) �ع���=365.24321
    1947180.798300,15.218524844, //  619-02-03 h=0.00052 �����顤��־(����Ԫ��)ƽ����˷ �ع���=365.24460
    1964362.041824,15.218533526, //  666-02-17 h=0.00059 �����顤��־(�����) �ع���=365.24480
    1987372.340971,15.218513908, //  729-02-16 h=0.00096 �����顤��־(������,������) �ع���=365.24433
    1999653.819126,15.218530782, //  762-10-03 h=0.00093 �����顤��־(�����) �ع���=365.24474
    2007445.469786,15.218535181, //  784-02-01 h=0.00059 �����顤��־(��Ԫ��,������) �ع���=365.24484
    2021324.917146,15.218526248, //  822-02-01 h=0.00022 �����顤��־(������) �ع���=365.24463
    2047257.232342,15.218519654, //  893-01-31 h=0.00015 �����顤��־(������) �ع���=365.24447
    2070282.898213,15.218425000, //  956-02-16 h=0.00149 ���������־(������) �ع���=365.24220
    2073204.872850,15.218515221, //  964-02-16 h=0.00166 ��ʷ������־(Ӧ����) �ع���=365.24437
    2080144.500926,15.218530782, //  983-02-16 h=0.00093 ��ʷ������־(ǬԪ��) �ع���=365.24474
    2086703.688963,15.218523776, // 1001-01-31 h=0.00067 ��ʷ������־(������,������) �ع���=365.24457
    2110033.182763,15.218425000, // 1064-12-15 h=0.00669 ��ʷ������־(������) �ع���=365.24220
    2111190.300888,15.218425000, // 1068-02-15 h=0.00149 ��ʷ������־(������) �ع���=365.24220
    2113731.271005,15.218515671, // 1075-01-30 h=0.00038 ������(��Ԫ��) �ع���=365.24438
    2120670.840263,15.218425000, // 1094-01-30 h=0.00149 ��ʷ������־ �ع���=365.24220
    2123973.309063,15.218425000, // 1103-02-14 h=0.00669 ������(ռ����) �ع���=365.24220
    2125068.997336,15.218477932, // 1106-02-14 h=0.00056 ��ʷ������־(��Ԫ��) �ع���=365.24347
    2136026.312633,15.218472436, // 1136-02-14 h=0.00088 ��ʷ������־(ͳԪ��,Ǭ����,������) �ع���=365.24334
    2156099.495538,15.218425000, // 1191-01-29 h=0.00149 ��ʷ������־(��Ԫ��) �ع���=365.24220
    2159021.324663,15.218425000, // 1199-01-29 h=0.00149 ��ʷ������־(ͳ����) �ع���=365.24220
    2162308.575254,15.218461742, // 1208-01-30 h=0.00146 ��ʷ������־(������) �ع���=365.24308
    2178485.706538,15.218425000, // 1252-05-15 h=0.04606 ���v�� �ع���=365.24220
    2178759.662849,15.218445786, // 1253-02-13 h=0.00231 ������ �ع���=365.24270
    2185334.020800,15.218425000, // 1271-02-13 h=0.00520 ��ʷ������־(������) �ع���=365.24220
    2187525.481425,15.218425000, // 1277-02-12 h=0.00520 ������ �ع���=365.24220
    2188621.191481,15.218437484, // 1280-02-13 h=0.00013 Ԫʷ����־(���ؾ���ʱ��) �ع���=365.24250
    2321919.49// 1645-02-04
};

MoonCalculate::MoonCalculate(): leap(0), HS(32, 0.0), dx(32, 0.0), ym(14, chineseNum::ZHENG_VAL)
{
    int i = 0;
    for(i = 0; i < 23; ++i)
        suoKB.push_back(suoKBArray[i]);
    for(i = 0; i < 71; ++i)
        qiKB.push_back(qiKBArray[i]);

    SB = init(1);
    QB = init(0);
}

/// <summary>
/// �;��ȶ�˷����,��2000����600�������2Сʱ����(�ԱȹŴ�������׼�ܶ�)
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double MoonCalculate::so_low(double W)
{
    double v = 7771.37714500204;
    double t = (W + 1.08472) / v;
    t -= (-0.0000331 * t * t
        + 0.10976 * cos(0.785 + 8328.6914 * t)
        + 0.02224 * cos(0.187 + 7214.0629 * t)
        - 0.03342 * cos(4.669 + 628.3076 * t)) / v
        + (32 * (t + 1.8) * (t + 1.8) - 20) / 86400 / 36525;
    return t * 36525 + 8.0 / 24.0;
}

/// <summary>
/// �;��ȶ�������, ������С��30���ӣ�ƽ��5��
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double  MoonCalculate::qi_low(double W)
{
    double t, L, v = 628.3319653318;
    t = (W - 4.895062166) / v; //��һ�ι���,���2������
    t -= (53 * t * t + 334116 * cos(4.67 + 628.307585 * t) + 2061 * cos(2.678 + 628.3076 * t) * t) / v / 10000000; //�ڶ��ι���,���2Сʱ����

    L = 48950621.66 + 6283319653.318 * t + 53 * t * t    //ƽ�ƾ�
        + 334166 * cos(4.669257 + 628.307585 * t)   //������Բ�������չ��
        + 3489 * cos(4.6261 + 1256.61517 * t)       //������Բ�������չ��
        + 2060.6 * cos(2.67823 + 628.307585 * t) * t  //һ�β�����
        - 994 - 834 * sin(2.1824 - 33.75705 * t);     //���в����¶�����

    t -= (L / 10000000 - W) / 628.332 + (32 * (t + 1.8) * (t + 1.8) - 20) / 86400 / 36525;
    return t * 36525 + 8.0 / 24.0;
}

/// <summary>
/// �ϸ߾��ȶ�������
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double MoonCalculate::qi_high(double W)
{
    JulianDay julianDay;
    StarCalendar starCalendar;
    double t = starCalendar.S_aLon_t2(W) * 36525;
    t = t - julianDay.deltatT2(t) + 8.0 / 24.0;
    double v = (fmod((t + 0.5), 1)) * 86400;
    if (v < 600 || v > 86400 - 600) t = starCalendar.S_aLon_t(W) * 36525 - julianDay.deltatT2(t) + 8.0 / 24.0;
    return t;
}

/// <summary>
/// �ϸ߾���˷����
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double MoonCalculate::so_high(double W)
{
    JulianDay julianDay;
    StarCalendar starCalendar;
    double t = starCalendar.MS_aLon_t2(W) * 36525;
    t = t - julianDay.deltatT2(t) + 8.0 / 24.0;
    double v = (fmod((t + 0.5), 1)) * 86400;
    if (v < 600 || v > 86400 - 600) t = starCalendar.MS_aLon_t(W) * 36525 - julianDay.deltatT2(t) + 8.0 / 24.0;
    return t;
}

/// <summary>
/// ��ʹ��: ˷������, ��������
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
std::string MoonCalculate::init(int type)
{
    std::string suoS;
    std::string qiS;
    //  619-01-21��ʼ16598��˷�������� d0=1947168
    suoS.append("EqoFscDcrFpmEsF2DfFideFelFpFfFfFiaipqti1ksttikptikqckstekqttgkqttgkqteksttikptikq2fjstgjqttjkqttgkqt");
    suoS.append("ekstfkptikq2tijstgjiFkirFsAeACoFsiDaDiADc1AFbBfgdfikijFifegF1FhaikgFag1E2btaieeibggiffdeigFfqDfaiBkF");
    suoS.append("1kEaikhkigeidhhdiegcFfakF1ggkidbiaedksaFffckekidhhdhdikcikiakicjF1deedFhFccgicdekgiFbiaikcfi1kbFibef");
    suoS.append("gEgFdcFkFeFkdcfkF1kfkcickEiFkDacFiEfbiaejcFfffkhkdgkaiei1ehigikhdFikfckF1dhhdikcfgjikhfjicjicgiehdik");
    suoS.append("cikggcifgiejF1jkieFhegikggcikFegiegkfjebhigikggcikdgkaFkijcfkcikfkcifikiggkaeeigefkcdfcfkhkdgkegieid");
    suoS.append("hijcFfakhfgeidieidiegikhfkfckfcjbdehdikggikgkfkicjicjF1dbidikFiggcifgiejkiegkigcdiegfggcikdbgfgefjF1");
    suoS.append("kfegikggcikdgFkeeijcfkcikfkekcikdgkabhkFikaffcfkhkdgkegbiaekfkiakicjhfgqdq2fkiakgkfkhfkfcjiekgFebicg");
    suoS.append("gbedF1jikejbbbiakgbgkacgiejkijjgigfiakggfggcibFifjefjF1kfekdgjcibFeFkijcfkfhkfkeaieigekgbhkfikidfcje");
    suoS.append("aibgekgdkiffiffkiakF1jhbakgdki1dj1ikfkicjicjieeFkgdkicggkighdF1jfgkgfgbdkicggfggkidFkiekgijkeigfiski");
    suoS.append("ggfaidheigF1jekijcikickiggkidhhdbgcfkFikikhkigeidieFikggikhkffaffijhidhhakgdkhkijF1kiakF1kfheakgdkif");
    suoS.append("iggkigicjiejkieedikgdfcggkigieeiejfgkgkigbgikicggkiaideeijkefjeijikhkiggkiaidheigcikaikffikijgkiahi1");
    suoS.append("hhdikgjfifaakekighie1hiaikggikhkffakicjhiahaikggikhkijF1kfejfeFhidikggiffiggkigicjiekgieeigikggiffig");
    suoS.append("gkidheigkgfjkeigiegikifiggkidhedeijcfkFikikhkiggkidhh1ehigcikaffkhkiggkidhh1hhigikekfiFkFikcidhh1hit");
    suoS.append("cikggikhkfkicjicghiediaikggikhkijbjfejfeFhaikggifikiggkigiejkikgkgieeigikggiffiggkigieeigekijcijikgg");
    suoS.append("ifikiggkideedeijkefkfckikhkiggkidhh1ehijcikaffkhkiggkidhh1hhigikhkikFikfckcidhh1hiaikgjikhfjicjicgie");
    suoS.append("hdikcikggifikigiejfejkieFhegikggifikiggfghigkfjeijkhigikggifikiggkigieeijcijcikfksikifikiggkidehdeij");
    suoS.append("cfdckikhkiggkhghh1ehijikifffffkhsFngErD1pAfBoDd1BlEtFqA2AqoEpDqElAEsEeB2BmADlDkqBtC1FnEpDqnEmFsFsAFn");
    suoS.append("llBbFmDsDiCtDmAB2BmtCgpEplCpAEiBiEoFqFtEqsDcCnFtADnFlEgdkEgmEtEsCtDmADqFtAFrAtEcCqAE1BoFqC1F1DrFtBmF");
    suoS.append("tAC2ACnFaoCgADcADcCcFfoFtDlAFgmFqBq2bpEoAEmkqnEeCtAE1bAEqgDfFfCrgEcBrACfAAABqAAB1AAClEnFeCtCgAADqDoB");
    suoS.append("mtAAACbFiAAADsEtBqAB2FsDqpFqEmFsCeDtFlCeDtoEpClEqAAFrAFoCgFmFsFqEnAEcCqFeCtFtEnAEeFtAAEkFnErAABbFkAD");
    suoS.append("nAAeCtFeAfBoAEpFtAABtFqAApDcCGJ");
    //1645-02-03��ʼ7582������������
    qiS.append("EmcFs22AFsckF2tsDtFqEtF1posFdFgiFseFtmelpsEfhkF2anmelpFlF1ikrotcnEqEq2FfqmcDsrFor22FgFrcgDscFs22FgEe");
    qiS.append("FtE2sfFs22sCoEsaF2tsD1FpeE2eFsssEciFsFnmelpFcFhkF2tcnEqEpFgkrotcnEqrEtFermcDsrE222FgBmcmr22DaEfnaF22");
    qiS.append("2sD1FpeForeF2tssEfiFpEoeFssD1iFstEqFppDgFstcnEqEpFg11FscnEqrAoAF2ClAEsDmDtCtBaDlAFbAEpAAAAAD2FgBiBqo");
    qiS.append("BbnBaBoAAAAAAAEgDqAdBqAFrBaBoACdAAf1AACgAAAeBbCamDgEifAE2AABa1C1BgFdiAAACoCeE1ADiEifDaAEqAAFe1AcFbcA");
    qiS.append("AAAAF1iFaAAACpACmFmAAAAAAAACrDaAAADG0");

    if (type == 1)
    {
        QiShuoDataUnCompress qiShouUnCompress(suoS);
        return qiShouUnCompress.UnCompress();
    }
    else
    {
        QiShuoDataUnCompress qiShouUnCompress(qiS);
        return qiShouUnCompress.UnCompress();
    }
}

/// <summary>
/// jd Ӧ������Ҫȡ�õ���˷��, ������ qs=calc::Qi ʱ���������������
/// </summary>
/// <param name="jd"></param>
/// <param name="qs"></param>
/// <returns></returns>
double MoonCalculate::calc(double jd, calc::Calc_Type qs)
{
    unsigned int i;
    double D;
    std::string n;
    std::vector<double>* B = &suoKB;
    double pc = 14; 
    
    if (qs == calc::Qi) 
    {
        B = &qiKB; 
        pc = 7;
    }

    double f1 = (*B)[0] - pc;
    double f2 = (*B)[(*B).size() - 1] - pc;
    double f3 = 2436935;

    jd += commonDef::J2000;   

    if (jd < f1 || jd >= f3)
    { 
        // ƽ��˷�����׸�֮ǰ��ʹ���ִ������㷨��1960.1.1�Ժ�ʹ���ִ������㷨 (��һ���ֵ�����qi_high��so_high,������������֧��)
        if (qs == calc::Qi) 
            return floor(qi_high(floor((jd + pc - 2451259) / 365.2422 * 24) * M_PI / 12) + 0.5); //2451259��1999.3.21,̫���ӻƾ�Ϊ0,����.��������
        else 
            return floor(so_high(floor((jd + pc - 2451551) / 29.5306) * M_PI * 2) + 0.5); //2451551��2000.1.7���Ǹ�˷��,�ƾ���Ϊ0.��˷����
    }

    if (jd >= f1 && jd < f2)
    { 
        // ƽ����ƽ˷
        for (i = 0; i < (*B).size(); i += 2) if (jd + pc < (*B)[i + 2]) 
            break;
        D = (*B)[i] + (*B)[i + 1] * floor((jd + pc - (*B)[i]) / (*B)[i + 1]);
        D = floor(D + 0.5);
        if (D == 1683460) D++; //���ʹ��̫��������-103��1��24�յ�˷��,����õ�����23��,��������Ϊ24��(ʵ��)���������Բ�Ӱ��-103�������������ʹ���غ������õ�����24�գ�����D���ᱻִ�С�
        return D - commonDef::J2000;    // C#: ��Ϊ����
    }

    if (jd >= f2 && jd < f3)
    { 
        // ������˷
        if (qs == calc::Qi)
        {
            D = floor(qi_low(floor((jd + pc - 2451259) / 365.2422 * 24) * M_PI / 12) + 0.5); //2451259��1999.3.21,̫���ӻƾ�Ϊ0,����.��������
            n = QB.substr((int)(floor((jd - f2) / 365.2422 * 24)), 1); //�Ҷ�������ֵ
        }
        else
        {
            D = floor(so_low(floor((jd + pc - 2451551) / 29.5306) * M_PI * 2) + 0.5); //2451551��2000.1.7���Ǹ�˷��,�ƾ���Ϊ0.��˷����
            n = SB.substr((int)(floor((jd - f2) / 29.5306)), 1); //�Ҷ�˷����ֵ
        }
        if (n == "1") return D + 1;
        if (n == "2") return D - 1;
        return D;
    }

    return 0;    
}

// ������(����ʵ������),�ڵ���calcY()��õ���������
// ʱ��ϵͳȫ��ʹ�ñ���ʱ����ʹ������ʱ�̵������Ҳ��ʹ�ñ���ʱ
// �������������ʹ�ñ���ʱ���������ʾ���ң������ص����޷�������ȶ�

/// <summary>
/// ũ�����������,�ɶ���ũ��,��Ч��Χ����������֮��(����һ �� d �� ������)
/// </summary>
/// <param name="jd"></param>
void MoonCalculate::calcY(double jd)
{
    int i;
    double W, w;

    // �������
    W = floor((jd - 355 + 183) / 365.2422) * 365.2422 + 355;  // 355��2000.12����,�õ��Ͽ���jd�Ķ�������ֵ
    if (calc(W, calc::Qi) > jd) W -= 365.2422;
    for (i = 0; i < 25; i++) ZQ.lunarInfoList_[i] = calc(W + 15.2184 * i, calc::Qi);     // 25������ʱ��(����ʱ��),�Ӷ�����ʼ����һ�������Ժ�
    ZQ.pe1 = calc(W - 15.2, calc::Qi); ZQ.pe2 = calc(W - 30.4, calc::Qi);  // �������,ȷ��һ���������·ݵġ�����ȫ������������

    // ����"��˷"�����»ƾ���w
    w = calc(ZQ.lunarInfoList_[0], calc::Shuo);    // ��Ͽ���������˷��
    if (w > ZQ.lunarInfoList_[0]) w -= 29.53;

    // ��������˷,����14���µ�ʼĩ
    for (i = 0; i < 15; i++)
    {
        HS[i] = calc(w + 29.5306 * i, calc::Shuo);
    }

    // �´�С
    double ymArr[20] = {0};
    leap = 0;
    for (i = 0; i < 14; i++)
    {
        dx[i] = HS[i + 1] - HS[i]; // �´�С
        ymArr[i] = i;  // �����ʼ��
    }

    // -721����-104��ĺ���¼��½�����,��˷�йأ������޹�
    double YY = floor((ZQ.lunarInfoList_[0] + 10 + 180) / 365.2422) + 2000; // ȷ�����
    if (YY >= -721 && YY <= -104)
    {
        double ly = 0, b0 = 0, k0 = 0, x0 = 0;    // lyΪ��Ԫ(�������µ�������),x0�½�,lName��������,b0,k0Ϊ������ϲ���
        std::string lName = "";
        if (YY >= -721) { ly = 1457698 - commonDef::J2000; k0 = 12.368422; b0 = 0.342; lName = "ʮ��"; x0 = 2; }    // ������,lyΪ-722.12.17
        if (YY >= -479) { ly = 1546083 - commonDef::J2000; k0 = 12.368422; b0 = 0.500; lName = "ʮ��"; x0 = 2; }    // ս����,lyΪ-480.12.11
        if (YY >= -220) { ly = 1640641 - commonDef::J2000; k0 = 12.369000; b0 = 0.866; lName = "���"; x0 = 11; }   // �غ���,lyΪ-221.10.31;
        double nY = floor((HS[0] - ly + 100) / 365.25);    // �����
        double f1 = floor(b0 + nY * k0), f2 = floor(b0 + nY * k0 + k0), f3;    // f1�б����׵��»���,f2Ϊ��һ���׵��»���
        f1 = floor(f1); f2 = floor(f2);
        for (i = 0; i < 14; i++)
        {
            f3 = floor((HS[i] - ly + 15) / 29.5306);    // ���»���
            if (f3 < f2) 
                f3 -= f1; 
            else 
                f3 -= f2;

            if (f3 < 12) 
                ym[i] = commonDef::CHINESE_MONTH_TABLE[(int)fmod((f3 + x0), 12)]; 
            else 
                ym[i] = lName;
        }
    }

    // ����������ȷ������,(��˷��Ϸ�,����Դ���ж�����ʼ�ĵ�����˷)
    if (HS[13] <= ZQ.lunarInfoList_[24])
    { 
        // ��13�µ���ĩû�г�������(��������),˵�����꺬��13����
        for (i = 1; HS[i + 1] > ZQ.lunarInfoList_[2 * i] && i < 13; i++) ; //��13�������ҵ�1��û���������·�
        leap = i;
        for (; i < 14; i++) 
            ymArr[i] = ymArr[i] - 1;  // �����ʼ��;
    }

    // ����ת��(�½�����)
    for (i = 0; i < 14; i++)
    {
        double Dm = HS[i] + commonDef::J2000;
        double v2 = ymArr[i];  // Dm��һ��������,v2Ϊ�½����
        chineseNum::CNUM_TYPE mc = commonDef::CHINESE_MONTH_TABLE[(int)fmod(v2, 12)];    // �½���Ӧ��Ĭ�������ƣ�����ʮһ,����ʮ��,����Ϊ������
        if (Dm >= 1724360 && Dm <= 1729794) mc = commonDef::CHINESE_MONTH_TABLE[(int)fmod((v2 + 1), 12)];        //  8.01.15�� 23.12.02 ����Ϊʮ��,����˳��
        else if (Dm >= 1807724 && Dm <= 1808699) mc = commonDef::CHINESE_MONTH_TABLE[(int)fmod((v2 + 1), 12)];   // 237.04.12��239.12.13 ����Ϊʮ��,����˳��
        else if (Dm >= 1999349 && Dm <= 1999467) mc = commonDef::CHINESE_MONTH_TABLE[(int)fmod((v2 + 2), 12)];   // 761.12.02��762.03.30 ����Ϊ����,����˳��
        else if (Dm >= 1973067 && Dm <= 1977112) 
        { 
            if ((int)fmod(v2, 12) == 0) 
                mc = chineseNum::ZHENG_VAL; 
            if (v2 == 2) 
                mc = chineseNum::ONE_VAL; 
        }    // 689.12.18��701.01.14 ����Ϊ����,����Ϊһ��,��������

        if (Dm == 1729794 || Dm == 1808699) 
            mc = chineseNum::TWELVE_VAL;    // 239.12.13��23.12.02��Ϊʮ����,Ϊ������������ʮ���£��˴�����

        ym[i] = mc;
    }
}

/// <summary>
/// ��������: �������, �����ؼ���Ľ�������, �ڵ��ñ���������ȡ ZQ ���ݺ�, Ӧ������ ZQ
/// </summary>
/// <param name="jd"></param>
/// <param name="calcMultiPeriod"></param>
/// <returns></returns>
int MoonCalculate::calcJieQi(double jd, commonDef::LunarInfo& zq, bool calcMultiPeriod)
{
    int i;
    double W;
    if (!calcMultiPeriod)    // ֻ����ĳ��Ľ���
    {
        W = floor((jd - 355 + 183) / 365.2422) * 365.2422 + 355;  // 355��2000.12����,�õ��Ͽ���jd�Ķ�������ֵ
        if (calc(W, calc::Qi) > jd) W -= 365.2422;
        for (i = 0; i < 25; i++) zq.lunarInfoList_[i] = calc(W + 15.2184 * i, calc::Qi);     // 25������ʱ��(����ʱ��),�Ӷ�����ʼ����һ�������Ժ�
        zq.pe1 = calc(W - 15.2, calc::Qi); zq.pe2 = calc(W - 30.4, calc::Qi);  // �������,ȷ��һ���������·ݵġ�����ȫ������������
    }
    else    // ������˪������ 2 ����֮��Ľ���, ���ڼ���ָ�����ڵ���������, ��һ����, ��һ��������Ϣ
    {
        W = floor((jd - 355 + 183) / 365.2422) * 365.2422 + 296;  // 296��2000.10.23˪��(��200.1.1������),�õ��Ͽ���jd��˪������ֵ
        if (calc(W, calc::Qi) > jd) W -= 365.2422;
        for (i = 0; i < 31; i++) zq.lunarInfoList_[i] = calc(W + 15.2184 * i, calc::Qi);     // 31������ʱ��(����ʱ��),��˪������ʼ���� 2 �����Ժ�
    }
    return ((!calcMultiPeriod ? 25 : 31));
}

}  // namespace dateTime
}  // namespace YiEngine