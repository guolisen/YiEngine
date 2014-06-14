#ifndef YIENGINE_DATETIME_TRANSLATOR_H
#define YIENGINE_DATETIME_TRANSLATOR_H
#include <string>

namespace yiEngine
{
namespace dateTime
{

template <class T>
class YiBaseType
{
public:
    YiBaseType():valueStr_("") {}
    YiBaseType(T val, const char* targetData): 
        value_(val), valueStr_(targetData) {}
    YiBaseType(const std::string& valStr): valueStr_(valStr) {}
    virtual ~YiBaseType() {}

    operator bool()
    {
        return !valueStr_.empty();
    }

    operator int()
    {
        return (int)value_;
    }

    bool operator!=(const YiBaseType<T>& r)
    {
        return (value_ != r.value_);
    }

    bool operator==(const YiBaseType<T>& r)
    {
        return (value_ == r.value_);
    }
public:
    std::string valueStr_;
    T value_;
};

template<class T, class T1>
std::string operator+(const YiBaseType<T>& l, const YiBaseType<T1>& r)
{
    return l.valueStr_ + r.valueStr_;
}

template<class T>
std::string operator+(const std::string& l, const YiBaseType<T>& r)
{
    return l + r.valueStr_;
}

template<class T>
std::string operator+(const YiBaseType<T>& l, const std::string& r)
{
    return l.valueStr_ + r;
}

template<class T, class T1>
bool operator==(const YiBaseType<T>& l, const YiBaseType<T1>& r)
{
    return (l.value_ == r.value_) && (l.valueStr_ == r.valueStr_);
}

template<class T, class T1>
bool operator!=(const YiBaseType<T>& l, const YiBaseType<T1>& r)
{
    return (l.value_ != r.value_) || (l.valueStr_ != r.valueStr_);
}

template <class T, T val>
class Translator: public YiBaseType<T>
{
public:
    Translator(const char* targetData): YiBaseType(val, targetData) {}
};

typedef Translator<int, -1> internal_TWEIZHI;
const internal_TWEIZHI NONE_VAL("未知");

// ZHI
namespace zhi
{
    enum Zhi_Enum
    {
        ZI = 0,
        CHOU,
        YIN,
        MAO,
        CHEN,
        SI,
        WU,
        WEI,
        SHEN,
        YOU,
        XU,
        HAI
    };

    typedef Translator<zhi::Zhi_Enum, zhi::ZI> internal_TZI;
    const internal_TZI ZI_VAL("子");

    typedef Translator<zhi::Zhi_Enum, zhi::CHOU> internal_TCHOU;
    const internal_TCHOU CHOU_VAL("丑");

    typedef Translator<zhi::Zhi_Enum, zhi::YIN> internal_TYIN;
    const internal_TYIN YIN_VAL("寅");

    typedef Translator<zhi::Zhi_Enum, zhi::MAO> internal_TMAO;
    const internal_TMAO MAO_VAL("卯");

    typedef Translator<zhi::Zhi_Enum, zhi::CHEN> internal_TCHEN;
    const internal_TCHEN CHEN_VAL("辰");

    typedef Translator<zhi::Zhi_Enum, zhi::SI> internal_TSI;
    const internal_TSI SI_VAL("巳");

    typedef Translator<zhi::Zhi_Enum, zhi::WU> internal_TWU;
    const internal_TWU WU_VAL("午");

    typedef Translator<zhi::Zhi_Enum, zhi::WEI> internal_TWEI;
    const internal_TWEI WEI_VAL("未");

    typedef Translator<zhi::Zhi_Enum, zhi::SHEN> internal_TSHEN;
    const internal_TSHEN SHEN_VAL("申");

    typedef Translator<zhi::Zhi_Enum, zhi::YOU> internal_TYOU;
    const internal_TYOU YOU_VAL("酉");

    typedef Translator<zhi::Zhi_Enum, zhi::XU> internal_TXU;
    const internal_TXU XU_VAL("戌");

    typedef Translator<zhi::Zhi_Enum, zhi::HAI> internal_THAI;
    const internal_THAI HAI_VAL("亥");

    typedef YiBaseType<zhi::Zhi_Enum> ZHI_TYPE;
}

// GAN
namespace gan
{
    enum Gan_Enum
    {
        JIA = 0,
        YI,
        BING,
        DING,
        WU,
        JI,
        GENG,
        XIN,
        REN,
        GUI
    };

    typedef Translator<gan::Gan_Enum, gan::JIA> internal_TJIA;
    const internal_TJIA JIA_VAL("甲");

    typedef Translator<gan::Gan_Enum, gan::YI> internal_TYI;
    const internal_TYI YI_VAL("乙");

    typedef Translator<gan::Gan_Enum, gan::BING> internal_TBING;
    const internal_TBING BING_VAL("丙");

    typedef Translator<gan::Gan_Enum, gan::DING> internal_TDING;
    const internal_TDING DING_VAL("丁");

    typedef Translator<gan::Gan_Enum, gan::WU> internal_TWU;
    const internal_TWU WU_VAL("戊");

    typedef Translator<gan::Gan_Enum, gan::JI> internal_TJI;
    const internal_TJI JI_VAL("己");

    typedef Translator<gan::Gan_Enum, gan::GENG> internal_TGENG;
    const internal_TGENG GENG_VAL("庚");

    typedef Translator<gan::Gan_Enum, gan::XIN> internal_TXIN;
    const internal_TXIN XIN_VAL("辛");

    typedef Translator<gan::Gan_Enum, gan::REN> internal_TREN;
    const internal_TREN REN_VAL("壬");

    typedef Translator<gan::Gan_Enum, gan::GUI> internal_TGUI;
    const internal_TGUI GUI_VAL("癸");

    typedef YiBaseType<gan::Gan_Enum> GAN_TYPE;
}

namespace chineseNum
{
    enum Cnum_Enum
    {
        ZERO = 0,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        ELEVEN,
        TWELVE,
        THIRTEEN,
        FOURTEEN,
        FIFTEEN,
        SIXTEEN,
        SEVENTEEN,
        EIGHTEEN,
        NINETEEN,
        TWENTY,
        TWENTY_ONE,
        TWENTY_TWO,
        TWENTY_THREE,
        TWENTY_FOUR,
        TWENTY_FIVE,
        TWENTY_SIX,
        TWENTY_SEVEN,
        TWENTY_EIGHT,
        TWENTY_NINE,
        THIRTY,
        THIRTY_ONE,
        THIRTY_TWO,
        
        ZHENG  = ONE,
        CHU_YI = ONE,
        CHU_ER = TWO,
        CHU_SAN = THREE,
        CHU_SI  = FOUR,
        CHU_WU  = FIVE,
        CHU_LIU = SIX,
        CHU_QI  = SEVEN,
        CHU_BA  = EIGHT,
        CHU_JIU = NINE,
        CHU_SHI = TEN
    };

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::ZERO> internal_TZERO;
    const internal_TZERO ZERO_VAL("零");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::ONE> internal_TONE;
    const internal_TONE ONE_VAL("一");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWO> internal_TTWO;
    const internal_TTWO TWO_VAL("二");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::THREE> internal_TTHREE;
    const internal_TTHREE THREE_VAL("三");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::FOUR> internal_TFOUR;
    const internal_TFOUR FOUR_VAL("四");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::FIVE> internal_TFIVE;
    const internal_TFIVE FIVE_VAL("五");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::SIX> internal_TSIX;
    const internal_TSIX SIX_VAL("六");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::SEVEN> internal_TSEVEN;
    const internal_TSEVEN SEVEN_VAL("七");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::EIGHT> internal_TEIGHT;
    const internal_TEIGHT EIGHT_VAL("八");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::NINE> internal_TNINE;
    const internal_TNINE NINE_VAL("九");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TEN> internal_TTEN;
    const internal_TTEN TEN_VAL("十");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::ELEVEN> internal_TELEVEN;
    const internal_TELEVEN ELEVEN_VAL("十一");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWELVE> internal_TTWELVE;
    const internal_TTWELVE TWELVE_VAL("十二");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::THIRTEEN> internal_TTHIRTEEN;
    const internal_TTHIRTEEN THIRTEEN_VAL("十三");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::FOURTEEN> internal_TFOURTEEN;
    const internal_TFOURTEEN FOURTEEN_VAL("十四");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::FIFTEEN> internal_TFIFTEEN;
    const internal_TFIFTEEN FIFTEEN_VAL("十五");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::SIXTEEN> internal_TSIXTEEN;
    const internal_TSIXTEEN SIXTEEN_VAL("十六");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::SEVENTEEN> internal_TSEVENTEEN;
    const internal_TSEVENTEEN SEVENTEEN_VAL("十七");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::EIGHTEEN> internal_TEIGHTEEN;
    const internal_TEIGHTEEN EIGHTEEN_VAL("十八");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::NINETEEN> internal_TNINETEEN;
    const internal_TNINETEEN NINETEEN_VAL("十九");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY> internal_TTWENTY;
    const internal_TTWENTY TWENTY_VAL("二十");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_ONE> internal_TTWENTY_ONE;
    const internal_TTWENTY_ONE TWENTY_ONE_VAL("廿一");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_TWO> internal_TTWENTY_TWO;
    const internal_TTWENTY_TWO TWENTY_TWO_VAL("廿二");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_THREE> internal_TTWENTY_THREE;
    const internal_TTWENTY_THREE TWENTY_THREE_VAL("廿三");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_FOUR> internal_TTWENTY_FOUR;
    const internal_TTWENTY_FOUR TWENTY_FOUR_VAL("廿四");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_FIVE> internal_TTWENTY_FIVE;
    const internal_TTWENTY_FIVE TWENTY_FIVE_VAL("廿五");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_SIX> internal_TTWENTY_SIX;
    const internal_TTWENTY_SIX TWENTY_SIX_VAL("廿六");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_SEVEN> internal_TTWENTY_SEVEN;
    const internal_TTWENTY_SEVEN TWENTY_SEVEN_VAL("廿七");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_EIGHT> internal_TTWENTY_EIGHT;
    const internal_TTWENTY_EIGHT TWENTY_EIGHT_VAL("廿八");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::TWENTY_NINE> internal_TTWENTY_NINE;
    const internal_TTWENTY_NINE TWENTY_NINE_VAL("廿九");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::THIRTY> internal_TTHIRTY;
    const internal_TTHIRTY THIRTY_VAL("三十");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::THIRTY_ONE> internal_TTHIRTY_ONE;
    const internal_TTHIRTY_ONE THIRTY_ONE_VAL("卅一");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::THIRTY_TWO> internal_TTHIRTY_TWO;
    const internal_TTHIRTY_TWO THIRTY_TWO_VAL("卅二");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::ZHENG> internal_TZHENG;
    const internal_TZHENG ZHENG_VAL("正");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_YI> internal_TCHU_YI;
    const internal_TCHU_YI CHU_YI_VAL("初一");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_ER> internal_TCHU_ER;
    const internal_TCHU_ER CHU_ER_VAL("初二");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_SAN> internal_TCHU_SAN;
    const internal_TCHU_SAN CHU_SAN_VAL("初三");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_SI> internal_TCHU_SI;
    const internal_TCHU_SI CHU_SI_VAL("初四");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_WU> internal_TCHU_WU;
    const internal_TCHU_WU CHU_WU_VAL("初五");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_LIU> internal_TCHU_LIU;
    const internal_TCHU_LIU CHU_LIU_VAL("初六");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_QI> internal_TCHU_QI;
    const internal_TCHU_QI CHU_QI_VAL("初七");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_BA> internal_TCHU_BA;
    const internal_TCHU_BA CHU_BA_VAL("初八");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_JIU> internal_TCHU_JIU;
    const internal_TCHU_JIU CHU_JIU_VAL("初九");

    typedef Translator<chineseNum::Cnum_Enum, chineseNum::CHU_SHI> internal_TCHU_SHI;
    const internal_TCHU_SHI CHU_SHI_VAL("初十");

    typedef YiBaseType<chineseNum::Cnum_Enum> CNUM_TYPE;
}

namespace shuXiang
{
    enum Shuxiang_Enum
    {
        MOUSE,
        CATTLE,
        TIGER,
        RABBIT,
        DRAGON,
        SNAKE,
        HORSE,
        SHEEP,
        MONKEY,
        CHIKEN,
        DOG,
        PIG
    };

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::MOUSE> internal_TMOUSE;
    const internal_TMOUSE MOUSE_VAL("鼠");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::CATTLE> internal_TCATTLE;
    const internal_TCATTLE CATTLE_VAL("牛");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::TIGER> internal_TTIGER;
    const internal_TTIGER TIGER_VAL("虎");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::RABBIT> internal_TRABBIT;
    const internal_TRABBIT RABBIT_VAL("兔");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::DRAGON> internal_TDRAGON;
    const internal_TDRAGON DRAGON_VAL("龙");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::SNAKE> internal_TSNAKE;
    const internal_TSNAKE SNAKE_VAL("蛇");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::HORSE> internal_THORSE;
    const internal_THORSE HORSE_VAL("马");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::SHEEP> internal_TSHEEP;
    const internal_TSHEEP SHEEP_VAL("羊");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::MONKEY> internal_TMONKEY;
    const internal_TMONKEY MONKEY_VAL("猴");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::CHIKEN> internal_TCHIKEN;
    const internal_TCHIKEN CHIKEN_VAL("鸡");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::DOG> internal_TDOG;
    const internal_TDOG DOG_VAL("狗");

    typedef Translator<shuXiang::Shuxiang_Enum, shuXiang::PIG> internal_TPIG;
    const internal_TPIG PIG_VAL("猪");

    typedef YiBaseType<shuXiang::Shuxiang_Enum> SHUXIANG_TYPE;
}

namespace constellation
{
    enum Constellation_Enum
    {
        CAPRICORN,
        AQUARIUS,
        PISCES,
        ARIES,
        TAURUS,
        GEMINI,
        CANCER,
        LEO,
        VIRGO,
        LIBRA,
        SCORPIO,
        SAGITTARIUS
    };

    typedef Translator<constellation::Constellation_Enum, constellation::CAPRICORN> internal_TCAPRICORN;
    const internal_TCAPRICORN CAPRICORN_VAL("摩羯");

    typedef Translator<constellation::Constellation_Enum, constellation::AQUARIUS> internal_TAQUARIUS;
    const internal_TAQUARIUS AQUARIUS_VAL("水瓶");

    typedef Translator<constellation::Constellation_Enum, constellation::PISCES> internal_TPISCES;
    const internal_TPISCES PISCES_VAL("双鱼");

    typedef Translator<constellation::Constellation_Enum, constellation::ARIES> internal_TARIES;
    const internal_TARIES ARIES_VAL("白羊");

    typedef Translator<constellation::Constellation_Enum, constellation::TAURUS> internal_TTAURUS;
    const internal_TTAURUS TAURUS_VAL("金牛");

    typedef Translator<constellation::Constellation_Enum, constellation::GEMINI> internal_TGEMINI;
    const internal_TGEMINI GEMINI_VAL("双子");

    typedef Translator<constellation::Constellation_Enum, constellation::CANCER> internal_TCANCER;
    const internal_TCANCER CANCER_VAL("巨蟹");

    typedef Translator<constellation::Constellation_Enum, constellation::LEO> internal_TLEO;
    const internal_TLEO LEO_VAL("狮子");

    typedef Translator<constellation::Constellation_Enum, constellation::VIRGO> internal_TVIRGO;
    const internal_TVIRGO VIRGO_VAL("处女");

    typedef Translator<constellation::Constellation_Enum, constellation::LIBRA> internal_TLIBRA;
    const internal_TLIBRA LIBRA_VAL("天枰");

    typedef Translator<constellation::Constellation_Enum, constellation::SCORPIO> internal_TSCORPIO;
    const internal_TSCORPIO SCORPIO_VAL("天蝎");

    typedef Translator<constellation::Constellation_Enum, constellation::SAGITTARIUS> internal_TSAGITTARIUS;
    const internal_TSAGITTARIUS SAGITTARIUS_VAL("人马");

    typedef YiBaseType<constellation::Constellation_Enum> CONSTELLATION_TYPE;
}

namespace lunarPhases
{
    enum LunarPhases_Enum
    {
        SHUO,
        SHANGXIAN,
        WANG,
        XIAXIAN
    };

    typedef Translator<lunarPhases::LunarPhases_Enum, lunarPhases::SHUO> internal_TSHUO;
    const internal_TSHUO SHUO_VAL("朔");

    typedef Translator<lunarPhases::LunarPhases_Enum, lunarPhases::SHANGXIAN> internal_TSHANGXIAN;
    const internal_TSHANGXIAN SHANGXIAN_VAL("上弦");

    typedef Translator<lunarPhases::LunarPhases_Enum, lunarPhases::WANG> internal_TWANG;
    const internal_TWANG WANG_VAL("望");

    typedef Translator<lunarPhases::LunarPhases_Enum, lunarPhases::XIAXIAN> internal_TXIAXIAN;
    const internal_TXIAXIAN XIAXIAN_VAL("下弦");

    typedef YiBaseType<lunarPhases::LunarPhases_Enum> LUNARPHASES_TYPE;
}


namespace jieqi
{
    enum Jieqi_Enum
    {
        DONGZHI,
        XIAOHAN,
        DAHAN,
        LICHUN,
        YUSHUI,
        JINGZHE,
        CHUNFEN,
        QINGMING,
        GUYU,
        LIXIA,
        XIAO_MAN,
        MANGZHONG,
        XIAZHI,
        XIAOSHU,
        DASHU,
        LIQIU,
        CHUSHU,
        BAILU,
        QIUFEN,
        HANLU,
        SHUANGJIANG,
        LIDONG,
        XIAOXUE,
        DAXUE
    };

    typedef Translator<jieqi::Jieqi_Enum, jieqi::DONGZHI> internal_TDONGZHI;
    const internal_TDONGZHI DONGZHI_VAL("冬至");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::XIAOHAN> internal_TXIAOHAN;
    const internal_TXIAOHAN XIAOHAN_VAL("小寒");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::DAHAN> internal_TDAHAN;
    const internal_TDAHAN DAHAN_VAL("大寒");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::LICHUN> internal_TLICHUN;
    const internal_TLICHUN LICHUN_VAL("立春");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::YUSHUI> internal_TYUSHUI;
    const internal_TYUSHUI YUSHUI_VAL("雨水");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::JINGZHE> internal_TJINGZHE;
    const internal_TJINGZHE JINGZHE_VAL("惊蛰");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::CHUNFEN> internal_TCHUNFEN;
    const internal_TCHUNFEN CHUNFEN_VAL("春分");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::QINGMING> internal_TQINGMING;
    const internal_TQINGMING QINGMING_VAL("清明");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::GUYU> internal_TGUYU;
    const internal_TGUYU GUYU_VAL("谷雨");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::LIXIA> internal_TLIXIA;
    const internal_TLIXIA LIXIA_VAL("立夏");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::XIAO_MAN> internal_TXIAO_MAN;
    const internal_TXIAO_MAN XIAO_MAN_VAL("小满");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::MANGZHONG> internal_TMANGZHONG;
    const internal_TMANGZHONG MANGZHONG_VAL("芒种");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::XIAZHI> internal_TXIAZHI;
    const internal_TXIAZHI XIAZHI_VAL("夏至");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::XIAOSHU> internal_TXIAOSHU;
    const internal_TXIAOSHU XIAOSHU_VAL("小暑");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::DASHU> internal_TDASHU;
    const internal_TDASHU DASHU_VAL("大暑");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::LIQIU> internal_TLIQIU;
    const internal_TLIQIU LIQIU_VAL("立秋");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::CHUSHU> internal_TCHUSHU;
    const internal_TCHUSHU CHUSHU_VAL("处暑");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::BAILU> internal_TBAILU;
    const internal_TBAILU BAILU_VAL("白露");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::QIUFEN> internal_TQIUFEN;
    const internal_TQIUFEN QIUFEN_VAL("秋分");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::HANLU> internal_THANLU;
    const internal_THANLU HANLU_VAL("寒露");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::SHUANGJIANG> internal_TSHUANGJIANG;
    const internal_TSHUANGJIANG SHUANGJIANG_VAL("霜降");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::LIDONG> internal_TLIDONG;
    const internal_TLIDONG LIDONG_VAL("立冬");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::XIAOXUE> internal_TXIAOXUE;
    const internal_TXIAOXUE XIAOXUE_VAL("小雪");

    typedef Translator<jieqi::Jieqi_Enum, jieqi::DAXUE> internal_TDAXUE;
    const internal_TDAXUE DAXUE_VAL("大雪");

    typedef YiBaseType<jieqi::Jieqi_Enum> JIEQI_TYPE;
}

namespace festival
{
    enum festival_Enum
    {
        CHU_XI,
        XIAO_NIAN,
        CHU,
        CHU_FU,
        ZHONG_FU,
        MUO_FU,
        RU_MEI,
        CHU_MEI,
        YI_JIU,
        ER_JIU,
        SAN_JIU,
        SI_JIU,
        WU_JIU,
        LIU_JIU,
        QI_JIU,
        BA_JIU,
        JIU_JIU
    };

    typedef Translator<festival::festival_Enum, festival::CHU_XI> internal_TCHU_XI;
    const internal_TCHU_XI CHU_XI_VAL("除夕");

    typedef Translator<festival::festival_Enum, festival::XIAO_NIAN> internal_TXIAO_NIAN;
    const internal_TXIAO_NIAN XIAO_NIAN_VAL("小年");

    typedef Translator<festival::festival_Enum, festival::CHU> internal_TCHU;
    const internal_TCHU CHU_VAL("初");

    typedef Translator<festival::festival_Enum, festival::CHU_FU> internal_TCHU_FU;
    const internal_TCHU_FU CHU_FU_VAL("初伏");

    typedef Translator<festival::festival_Enum, festival::ZHONG_FU> internal_TZHONG_FU;
    const internal_TZHONG_FU ZHONG_FU_VAL("中伏");

    typedef Translator<festival::festival_Enum, festival::MUO_FU> internal_TMUO_FU;
    const internal_TMUO_FU MUO_FU_VAL("末伏");

    typedef Translator<festival::festival_Enum, festival::RU_MEI> internal_TRU_MEI;
    const internal_TRU_MEI RU_MEI_VAL("入梅");

    typedef Translator<festival::festival_Enum, festival::CHU_MEI> internal_TCHU_MEI;
    const internal_TCHU_MEI CHU_MEI_VAL("出梅");

    typedef Translator<festival::festival_Enum, festival::YI_JIU> internal_TYI_JIU;
    const internal_TYI_JIU YI_JIU_VAL("一九");

    typedef Translator<festival::festival_Enum, festival::ER_JIU> internal_TER_JIU;
    const internal_TER_JIU ER_JIU_VAL("二九");

    typedef Translator<festival::festival_Enum, festival::SAN_JIU> internal_TSAN_JIU;
    const internal_TSAN_JIU SAN_JIU_VAL("三九");

    typedef Translator<festival::festival_Enum, festival::SI_JIU> internal_TSI_JIU;
    const internal_TSI_JIU SI_JIU_VAL("四九");

    typedef Translator<festival::festival_Enum, festival::WU_JIU> internal_TWU_JIU;
    const internal_TWU_JIU WU_JIU_VAL("五九");

    typedef Translator<festival::festival_Enum, festival::LIU_JIU> internal_TLIU_JIU;
    const internal_TLIU_JIU LIU_JIU_VAL("六九");

    typedef Translator<festival::festival_Enum, festival::QI_JIU> internal_TQI_JIU;
    const internal_TQI_JIU QI_JIU_VAL("七九");

    typedef Translator<festival::festival_Enum, festival::BA_JIU> internal_TBA_JIU;
    const internal_TBA_JIU BA_JIU_VAL("八九");

    typedef Translator<festival::festival_Enum, festival::JIU_JIU> internal_TJIU_JIU;
    const internal_TJIU_JIU JIU_JIU_VAL("九九");

    typedef YiBaseType<festival::festival_Enum> FESTIVAL_TYPE;
}


        // 日十二建表
        // private static string[] __RiJian12 = new string[] { "建", "除", "满", "平", "定", "执", "破", "危", "成", "收", "开", "闭" };




}  // namespace dateTime
}  // namespace YiEngine
#endif