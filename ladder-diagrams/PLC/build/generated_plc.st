PROGRAM program0
  VAR
    EntranceGateSensor AT %IX0.0 : BOOL;
    EntranceGateSensor0 AT %IX0.1 : BOOL;
    ticketValidationEnter AT %IX0.2 : BOOL;
    ticketValidationExit AT %IX2.4 : BOOL;
    PhysicalCardEnter AT %IX0.3 : BOOL;
    PhysicalCardExit AT %IX2.5 : BOOL;
    PermitCardEnter AT %IX0.7 : BOOL;
    PermitCardExit AT %IX2.6 : BOOL;
    openSpotSensor AT %IX1.1 : BOOL;
    countSensor AT %IX0.6 : BOOL;
    overstayNotification AT %IX0.5 : BOOL;
    OpenEntryGate AT %QX0.0 : BOOL;
    OverstaySignage AT %QX0.5 : BOOL;
    AvailableSpotSignage AT %QX0.8 : BOOL;
    LicensePlateCapture AT %IX1.0 : BOOL;
    LicensePlateVerification AT %IX5.1 : BOOL;
    EntrancePassThrough AT %IX0.8 : BOOL;
    AlarmButton AT %IX5.0 : BOOL;
    TempSensor AT %IX6.0 : BOOL;
    parkingLED AT %QX0.7 : BOOL;
    AlarmActivate AT %QX5.0 : BOOL;
    HealthDisplay AT %QX6.0 : BOOL;
    CloseEntryGate AT %QX0.6 : BOOL;
    LightSensor AT %IW2.0 : INT := 100;
    SetLight AT %IX2.4 : BOOL;
    RainSensor AT %IX2.1 : BOOL;
    SnowSensor AT %IX2.2 : BOOL;
    ClearWeather AT %IX2.3 : BOOL;
    LightControl AT %QX2.0 : BOOL;
    RainSignage AT %QX2.1 : BOOL;
    SnowSignage AT %QX2.2 : BOOL;
    ClearSignage AT %QX2.3 : BOOL;
  END_VAR
  VAR
    ParkingTimer : INT;
    ParkingLimit : INT := 60;
  END_VAR
  VAR
    ParkingDurationStatus AT %QX3.0 : BOOL;
    OverstayDetector AT %IX3.1 : BOOL;
    TicketValidationSensor AT %QX3.2 : BOOL;
    PaymentMachineDisplay AT %QX3.3 : BOOL;
    EVSensorStatus AT %IX4.0 : BOOL;
    EVChargerActivation AT %QX4.0 : BOOL;
    ExitSensor AT %IX0.4 : BOOL;
    ExitPassThroughSensor AT %IX0.8 : BOOL;
    LicensePlateCaptureSystem AT %QW0.1 : WORD;
    ExitGateOpens AT %QX0.4 : BOOL;
    ExitGateCloses AT %QX0.9 : BOOL;
  END_VAR
  VAR
    LightSensorCondition : INT := 10;
    _TMP_LE61_OUT : BOOL;
    _TMP_GT41_OUT : BOOL;
  END_VAR

  OpenEntryGate := (PermitCardEnter OR PhysicalCardEnter OR ticketValidationEnter) AND EntranceGateSensor;
  CloseEntryGate := EntrancePassThrough;
  OverstaySignage := overstayNotification AND ticketValidationEnter;
  LicensePlateCapture := ticketValidationEnter AND EntranceGateSensor AND PhysicalCardEnter AND EntranceGateSensor AND PermitCardEnter AND EntranceGateSensor;
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
  ExitGateOpens := (PermitCardExit OR PhysicalCardExit) AND ExitSensor;
  ExitGateCloses := ExitPassThroughSensor;
  TicketValidationSensor := ticketValidationExit;
  PaymentMachineDisplay := ticketValidationExit;
  ExitGateOpens := PaymentMachineDisplay;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
