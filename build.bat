@echo off
cls

echo ===========================================
echo        Building UniStay Rental System
echo ===========================================
echo.

g++ src/main.cpp src/authentication/Login.cpp src/property/Unit.cpp src/maintenance/Complaint.cpp src/users/Admin.cpp src/users/Tenant.cpp src/dsa/Sorting.cpp -o unistay.exe

if %errorlevel% neq 0 (
    echo.
    echo ===========================================
    echo                Build Failed!
    echo ===========================================
    pause
    exit
)

echo.
echo ===========================================
echo              Build Successful!
echo ===========================================
echo.

unistay.exe

echo.
pause