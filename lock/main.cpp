#include "main.h"

int main()
{
    ticker_scan_column.attach(ScanColumn, SCAN_COLUMN_PERIOD);

    char user_password_administrator_default[MAX_PW_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '9'};
    char user_password_default[MAX_PW_LENGTH] = {'5', '4', '3', '2', '1'};
    PW PW1(user_password_administrator_default, user_password_default);

    PW1.ResetUserInputBuffer();
    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
    while (true)
    {
        PW1.user_input = GetInput();
        ThisThread::sleep_for(INPUT_SENSITIVITY);
        // PW1.user_input = GetInput(); #TODO
        if (row_1 * row_2 * row_3 * row_4 == 0)
        {
            if (PW1.user_input == '#')
            {
                if (PW1.user_input_counter == 0)
                {
                    DisplayString("PRESS INPUT OLD PW");
                    // DisplayString("PRESS # TO CHANGE PASSWORD");
                    // DisplayString("PRESS OTHER TO CHANGE PW");
                    PW1.GetUserInputBuffer();
                    if (PW1.CheckPasswordAdministrator())
                    {
                        DisplayString("PLEASE INPUT NEW PW");
                        ticker_led.attach(ToggleGreenLED, 100ms);
                        PW1.GetUserInputBuffer();
                        PW1.UpdatePassword();
                        DisplayString("DONE");
                        ticker_led.detach();
                        PW1.ResetUserInputBuffer();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    }
                    else
                    {
                        ticker_led.attach(ToggleRedLED, 100ms);
                        DisplayString("WRONG");
                        ticker_led.detach();
                        PW1.ResetUserInputBuffer();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    }
                }
                else if (PW1.user_check_counter <= MAX_PW_INPUT_TIMES)
                {
                    if (PW1.CheckPassword())
                    {
                        ticker_led.attach(ToggleGreenLED, 100ms);
                        DisplayString("PASS");
                        ticker_led.detach();
                        PW1.ResetUserInputBuffer();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                        // #TODO 需要添加开门的函数
                    }
                    else
                    {
                        ticker_led.attach(ToggleRedLED, 100ms);
                        DisplayString("FAILED");
                        ticker_led.detach();
                        PW1.ResetUserInputBuffer();
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    }
                }
                else
                {
                    ticker_led.attach(ToggleRedLED, 100ms);
                    DisplayString("Please try again later");
                    ThisThread::sleep_for(PW_FALSE_SELLP_PERIOD);
                    ticker_led.detach();
                    PW1.ResetUserInputBuffer();
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    PW1.user_check_counter = 0;
                }
                // display.clear();
                // display.Home();
                // // int tempint = PW1.password_hash % 10000;
                // // display.printf("%d", tempint);
                // // display.printf("%d", PW1.password_hash);
                // display.printf("%c", PW1.user_input_buffer[3]);
                // // display.printf("%d", PW1.user_input_counter);
                // ThisThread::sleep_for(1000ms);
                // PW1.user_input_counter = 0;
            }
            else if (PW1.user_input == '*')
            {
                PW1.ResetUserInputBuffer();
                DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
            }
            else
            {
                if (PW1.user_input != PW1.user_input_buffer[0])
                {
                    timer_input.reset();
                    if (PW1.user_input_counter >= MAX_PW_LENGTH)
                    {
                        PW1.user_input_counter = MAX_PW_LENGTH; // #TODO
                    }
                    AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
                    DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                }
                else
                {
                    timer_input_end = timer_input.elapsed_time().count();
                    timer_input.reset();
                    timer_input.start();
                    if ((timer_input_end - timer_input_begin) > INPUT_INTERVAL)
                    {
                        if (PW1.user_input_counter >= MAX_PW_LENGTH)
                        {
                            PW1.user_input_counter = MAX_PW_LENGTH;
                        }
                        AppendBuffer(PW1.user_input_buffer, PW1.user_input, &PW1.user_input_counter);
                        DisplayInput(PW1.user_input_buffer, PW1.user_input_counter);
                    }
                    timer_input_begin = timer_input.elapsed_time().count();
                }
            }
        }
    }
}
