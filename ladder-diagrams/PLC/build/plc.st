TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM program0
  VAR
    EntranceGateSensor : BOOL;
    ticketValidation : BOOL;
    PhysicalCard : BOOL;
    PermitCard : BOOL;
    openSpotSensor : BOOL;
    countSensor : BOOL;
    overstayNotification : BOOL;
    OpenEntryGate : BOOL;
    OverstaySignage : BOOL;
    AvailableSpotSignage : BOOL;
    LicensePlateCapture : BOOL;
    LicensePlateVerification : BOOL;
    EntrancePassThrough : BOOL;
    AlarmButton : BOOL;
    TempSensor : BOOL;
    parkingLED : BOOL;
    AlarmActivate : BOOL;
    HealthDisplay : BOOL;
    CloseEntryGate : BOOL;
    LightSensor : INT := 100;
    SetLight : BOOL;
    RainSensor : BOOL;
    SnowSensor : BOOL;
    ClearWeather : BOOL;
    LightControl : BOOL;
    RainSignage : BOOL;
    SnowSignage : BOOL;
    ClearSignage : BOOL;
  END_VAR
  VAR
    ParkingTimer : INT;
    ParkingLimit : INT := 60;
  END_VAR
  VAR
    ParkingDurationStatus : BOOL;
    OverstayDetector : BOOL;
    TicketValidationSensor : BOOL;
    PaymentMachineDisplay : BOOL;
    EVSensorStatus : BOOL;
    EVChargerActivation : BOOL;
    ExitSensor : BOOL;
    ExitPassThroughSensor : BOOL;
    LicensePlateCaptureSystem : WORD;
    ExitGateOpens : BOOL;
    ExitGateCloses : BOOL;
  END_VAR
  VAR
    LightSensorCondition : INT := 10;
    _TMP_LE61_OUT : BOOL;
    _TMP_GT41_OUT : BOOL;
  END_VAR

  OpenEntryGate := (PermitCard OR PhysicalCard OR ticketValidation) AND EntranceGateSensor;
  CloseEntryGate := EntrancePassThrough;
  OverstaySignage := overstayNotification AND ticketValidation;
  LicensePlateCapture := ticketValidation AND EntranceGateSensor AND PhysicalCard AND EntranceGateSensor AND PermitCard AND EntranceGateSensor;
  AvailableSpotSignage := openSpotSensor;
  parkingLED := countSensor AND AvailableSpotSignage;
  AlarmActivate := AlarmButton;
  AlarmActivate := LicensePlateVerification;
  HealthDisplay := TempSensor;
  _TMP_LE61_OUT := LE(LightSensor, LightSensorCondition);
  LightControl := _TMP_LE61_OUT;
  RainSignage := RainSensor;
  SnowSignage := SnowSensor;
  ClearSignage := ClearWeather;
  _TMP_GT41_OUT := GT(ParkingTimer, ParkingLimit);
  ParkingDurationStatus := _TMP_GT41_OUT;
  overstayNotification := ParkingDurationStatus;
  EVChargerActivation := EVSensorStatus;
  LicensePlateCapture := ExitSensor;
  ExitGateOpens := (PermitCard OR PhysicalCard) AND ExitSensor;
  ExitGateCloses := ExitPassThroughSensor;
  TicketValidationSensor := ticketValidation;
  PaymentMachineDisplay := ticketValidation;
  ExitGateOpens := PaymentMachineDisplay;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
