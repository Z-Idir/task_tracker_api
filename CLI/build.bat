@echo off
gcc cmd_handler.c task_tracker.c  -o task_tracker ^
  -I"C:\Program Files\curl\include" ^
  -L"C:\Program Files\curl\lib" ^
  -lcurl ^
  -IcJson ^
  -LcJson ^
  -lcjson
