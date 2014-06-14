#include <iostream>
#include <YiEngine/YiEngine.h>
#include <windows.h>


int main()
{
    yiEngine::common::YiEnginePtr yiPtr = boost::make_shared<yiEngine::common::YiEngine>();
    yiEngine::dateTime::DateTimePtr dateTimeObj = yiPtr->GetDateTimeObject();
    yiEngine::sixYao::SixYaoPtr sixYaoObj = yiPtr->GetSixYaoObject();

    dateTimeObj->TestFun();
    
    yiEngine::dateTime::LunarDayObject tmpLObj;
    std::vector<yiEngine::dateTime::Day> tmpvec;
    for(int i = 1; i <= 100; ++i)
    {
        yiEngine::dateTime::Day tmpDay= dateTimeObj->GetDay(2014, 1, i, 0, 0, 0);
        tmpvec.push_back(tmpDay);
    }
    dateTimeObj->GetDayLunarInfo(tmpLObj, 2014, 4, 30, 0, 0, 0);
    yiEngine::dateTime::JulianDayInfo jd = dateTimeObj->GetJulianDay(2014, 3, 30, 0, 0, 0);
    yiEngine::dateTime::JulianDayInfo jd2 = dateTimeObj->GetJulianDay(5210.0 + yiEngine::dateTime::commonDef::J2000);

    sixYaoObj->TestFun();

    MSG msg;
    SetTimer(NULL, 1234, 1000, NULL); 
    while(GetMessage(&msg,0,0,0)) 
    { 
        if(msg.message==WM_TIMER) 
            dateTimeObj->TestFun();
    } 
	return 0;
}
