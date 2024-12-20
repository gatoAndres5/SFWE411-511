void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_VAR(data__->ENTRANCEGATESENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENTRANCEGATESENSOR0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TICKETVALIDATIONENTER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TICKETVALIDATIONEXIT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PHYSICALCARDENTER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PHYSICALCARDEXIT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PERMITCARDENTER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PERMITCARDEXIT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OPENSPOTSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->COUNTSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OVERSTAYNOTIFICATION,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OPENENTRYGATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OVERSTAYSIGNAGE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AVAILABLESPOTSIGNAGE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LICENSEPLATECAPTURE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LICENSEPLATEVERIFICATION,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENTRANCEPASSTHROUGH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ALARMBUTTON,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TEMPSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PARKINGLED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ALARMACTIVATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HEALTHDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CLOSEENTRYGATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHTSENSOR,100,retain)
  __INIT_VAR(data__->SETLIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RAINSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SNOWSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CLEARWEATHER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHTCONTROL,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RAINSIGNAGE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SNOWSIGNAGE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CLEARSIGNAGE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PARKINGTIMER,0,retain)
  __INIT_VAR(data__->PARKINGLIMIT,60,retain)
  __INIT_VAR(data__->PARKINGDURATIONSTATUS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OVERSTAYDETECTOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TICKETVALIDATIONSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PAYMENTMACHINEDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EVSENSORSTATUS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EVCHARGERACTIVATION,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EXITSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EXITPASSTHROUGHSENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LICENSEPLATECAPTURESYSTEM,0,retain)
  __INIT_VAR(data__->EXITGATEOPENS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EXITGATECLOSES,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHTSENSORCONDITION,10,retain)
  __INIT_VAR(data__->HMIENTRYDISPLAYTRIGGER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OVERSTAYPENALTYINDICATOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PARKINGSPOTDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ALARMSTATUSINDICATOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TEMPERATUREDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHTNINGSTATUSDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->WEATHERCONDITIONDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PARKINGDURATIONOVERSTAY,0,retain)
  __INIT_VAR(data__->EXITEVENTDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PAYMENTPROCESSDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SYSTEMHEALTHCHECKDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MANUALOVERRIDEGATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MANUALOVERRIDEALARM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MANUALOVERRIDELIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EVENTLOGDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STATUSSYNCTRIGGER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MAINTENANCEMODEDISPLAY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_LE61_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_GT41_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,OPENENTRYGATE,,(((__GET_VAR(data__->PERMITCARDENTER,) || __GET_VAR(data__->PHYSICALCARDENTER,)) || __GET_VAR(data__->TICKETVALIDATIONENTER,)) && __GET_VAR(data__->ENTRANCEGATESENSOR,)));
  __SET_VAR(data__->,CLOSEENTRYGATE,,__GET_VAR(data__->ENTRANCEPASSTHROUGH,));
  __SET_VAR(data__->,OVERSTAYSIGNAGE,,(__GET_VAR(data__->OVERSTAYNOTIFICATION,) && __GET_VAR(data__->TICKETVALIDATIONENTER,)));
  __SET_VAR(data__->,LICENSEPLATECAPTURE,,(((((__GET_VAR(data__->TICKETVALIDATIONENTER,) && __GET_VAR(data__->ENTRANCEGATESENSOR,)) && __GET_VAR(data__->PHYSICALCARDENTER,)) && __GET_VAR(data__->ENTRANCEGATESENSOR,)) && __GET_VAR(data__->PERMITCARDENTER,)) && __GET_VAR(data__->ENTRANCEGATESENSOR,)));
  __SET_VAR(data__->,AVAILABLESPOTSIGNAGE,,__GET_VAR(data__->OPENSPOTSENSOR,));
  __SET_VAR(data__->,PARKINGLED,,(__GET_VAR(data__->COUNTSENSOR,) && __GET_VAR(data__->AVAILABLESPOTSIGNAGE,)));
  __SET_VAR(data__->,ALARMACTIVATE,,__GET_VAR(data__->ALARMBUTTON,));
  __SET_VAR(data__->,ALARMACTIVATE,,__GET_VAR(data__->LICENSEPLATEVERIFICATION,));
  __SET_VAR(data__->,HEALTHDISPLAY,,__GET_VAR(data__->TEMPSENSOR,));
  __SET_VAR(data__->,_TMP_LE61_OUT,,LE__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->LIGHTSENSOR,),
    (INT)__GET_VAR(data__->LIGHTSENSORCONDITION,)));
  __SET_VAR(data__->,LIGHTCONTROL,,__GET_VAR(data__->_TMP_LE61_OUT,));
  __SET_VAR(data__->,RAINSIGNAGE,,__GET_VAR(data__->RAINSENSOR,));
  __SET_VAR(data__->,SNOWSIGNAGE,,__GET_VAR(data__->SNOWSENSOR,));
  __SET_VAR(data__->,CLEARSIGNAGE,,__GET_VAR(data__->CLEARWEATHER,));
  __SET_VAR(data__->,_TMP_GT41_OUT,,GT__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->PARKINGTIMER,),
    (INT)__GET_VAR(data__->PARKINGLIMIT,)));
  __SET_VAR(data__->,PARKINGDURATIONSTATUS,,__GET_VAR(data__->_TMP_GT41_OUT,));
  __SET_VAR(data__->,OVERSTAYNOTIFICATION,,__GET_VAR(data__->PARKINGDURATIONSTATUS,));
  __SET_VAR(data__->,EVCHARGERACTIVATION,,__GET_VAR(data__->EVSENSORSTATUS,));
  __SET_VAR(data__->,LICENSEPLATECAPTURE,,__GET_VAR(data__->EXITSENSOR,));
  __SET_VAR(data__->,EXITGATEOPENS,,((__GET_VAR(data__->PERMITCARDEXIT,) || __GET_VAR(data__->PHYSICALCARDEXIT,)) && __GET_VAR(data__->EXITSENSOR,)));
  __SET_VAR(data__->,EXITGATECLOSES,,__GET_VAR(data__->EXITPASSTHROUGHSENSOR,));
  __SET_VAR(data__->,TICKETVALIDATIONSENSOR,,__GET_VAR(data__->TICKETVALIDATIONEXIT,));
  __SET_VAR(data__->,PAYMENTMACHINEDISPLAY,,__GET_VAR(data__->TICKETVALIDATIONEXIT,));
  __SET_VAR(data__->,EXITGATEOPENS,,__GET_VAR(data__->PAYMENTMACHINEDISPLAY,));
  __SET_VAR(data__->,HMIENTRYDISPLAYTRIGGER,,__GET_VAR(data__->LICENSEPLATECAPTURE,));
  __SET_VAR(data__->,OVERSTAYPENALTYINDICATOR,,(__GET_VAR(data__->OVERSTAYNOTIFICATION,) && __GET_VAR(data__->TICKETVALIDATIONENTER,)));
  __SET_VAR(data__->,ALARMSTATUSINDICATOR,,__GET_VAR(data__->ALARMBUTTON,));
  __SET_VAR(data__->,PARKINGSPOTDISPLAY,,__GET_VAR(data__->OPENSPOTSENSOR,));
  __SET_VAR(data__->,ALARMSTATUSINDICATOR,,__GET_VAR(data__->LICENSEPLATEVERIFICATION,));
  __SET_VAR(data__->,TEMPERATUREDISPLAY,,__GET_VAR(data__->TEMPSENSOR,));
  __SET_VAR(data__->,LIGHTNINGSTATUSDISPLAY,,__GET_VAR(data__->_TMP_LE61_OUT,));
  __SET_VAR(data__->,WEATHERCONDITIONDISPLAY,,__GET_VAR(data__->RAINSENSOR,));
  __SET_VAR(data__->,WEATHERCONDITIONDISPLAY,,__GET_VAR(data__->SNOWSENSOR,));
  __SET_VAR(data__->,WEATHERCONDITIONDISPLAY,,__GET_VAR(data__->CLEARWEATHER,));
  __SET_VAR(data__->,PARKINGSPOTDISPLAY,,__GET_VAR(data__->_TMP_GT41_OUT,));
  __SET_VAR(data__->,OVERSTAYPENALTYINDICATOR,,__GET_VAR(data__->PARKINGDURATIONSTATUS,));
  __SET_VAR(data__->,EXITEVENTDISPLAY,,__GET_VAR(data__->EXITSENSOR,));
  __SET_VAR(data__->,EXITEVENTDISPLAY,,(((__GET_VAR(data__->PHYSICALCARDEXIT,) && __GET_VAR(data__->EXITSENSOR,)) && __GET_VAR(data__->PERMITCARDEXIT,)) && __GET_VAR(data__->EXITSENSOR,)));
  __SET_VAR(data__->,PAYMENTPROCESSDISPLAY,,__GET_VAR(data__->TICKETVALIDATIONEXIT,));
  __SET_VAR(data__->,PAYMENTPROCESSDISPLAY,,__GET_VAR(data__->TICKETVALIDATIONEXIT,));
  __SET_VAR(data__->,PAYMENTPROCESSDISPLAY,,__GET_VAR(data__->PAYMENTMACHINEDISPLAY,));
  __SET_VAR(data__->,SYSTEMHEALTHCHECKDISPLAY,,__GET_VAR(data__->HEALTHDISPLAY,));
  __SET_VAR(data__->,MANUALOVERRIDEALARM,,__GET_VAR(data__->ALARMSTATUSINDICATOR,));
  __SET_VAR(data__->,MANUALOVERRIDEGATE,,__GET_VAR(data__->OPENENTRYGATE,));
  __SET_VAR(data__->,EVENTLOGDISPLAY,,__GET_VAR(data__->OVERSTAYNOTIFICATION,));
  __SET_VAR(data__->,STATUSSYNCTRIGGER,,__GET_VAR(data__->PARKINGLED,));
  __SET_VAR(data__->,MANUALOVERRIDELIGHT,,__GET_VAR(data__->LIGHTCONTROL,));
  __SET_VAR(data__->,MANUALOVERRIDEGATE,,__GET_VAR(data__->EXITGATEOPENS,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





