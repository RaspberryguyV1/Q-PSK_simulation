% --- KONFIGURACJA (Musi się zgadzać z C++) ---

f_nosna = 1000; % Częstotliwość fali 
Fs = 4*f_nosna  ; % Częstotliwość próbkowania



% --- WCZYTANIE DANYCH ---

filename = 'sygnal.txt';

if ~isfile(filename)

error('Nie znaleziono pliku sygnal.txt! Uruchom najpierw kod C++.');

end

data = load(filename);

% --- OBLICZENIA OSI CZASU ---

N = length(data); 
t = (0:N-1) / Fs; 

% --- RYSOWANIE ---

figure('Name', 'Analiza Modulacji QPSK', 'Color', 'black');

% Wykres 1: Cały sygnał


plot(t, data, 'b');

title(['Caly sygnał (Dlugosc: ' num2str(t(end)) ' s)']);

xlabel('Czas [s]');

ylabel('Amplituda');

grid on;

ylim([-1.2 1.2]);
