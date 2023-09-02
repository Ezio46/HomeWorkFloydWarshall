clc; clear all; close all;


count = 0;
for i = 0:999999

    formatted_i = sprintf('%06d', i); % форматирую число в строку вида "000000"
    digits = formatted_i - '0'; % преобразую число в массив

    if sum(digits(1:3)) == sum(digits(4:6))
        count = count + 1;
    end

end

disp(['Количество счастливых 6-значных билетов: ', num2str(count)]);
