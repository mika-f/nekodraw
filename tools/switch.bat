@echo off

if exist ./NekoDraw.cpm_Debug (
  call :switch_debug_to_production
) else if exist ./NekoDraw.cpm_Release (
  call :switch_release_to_production
) else (
  call :err
)

exit /b

:switch_debug_to_production
echo switching debug build tp production
mv ./NekoDraw.cpm ./NekoDraw.cpm_Release
mv ./NekoDraw.cpm_Debug ./NekoDraw.cpm
exit /b

:switch_release_to_production
echo switching release build to production
mv ./NekoDraw.cpm ./NekoDraw.cpm_Debug
mv ./NekoDraw.cpm_Release ./NekoDraw.cpm
exit /b

:err
echo invalid state
exit /b