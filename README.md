# SOI_Monitors_lab4


PL:
Bufor n-elementowy FIFO (n > 3). Jest jeden producent i trzech 
konsumentów (A, B, C). Producent produkuje jeden element, jeżeli jest 
miejsce w buforze. Element jest usuwany z bufora, jeżeli zostanie 
przeczytany przez albo obu konsumentów A i B, albo przez obu konsumentów 
B i C. Konsument A nie może przeczytać elementu, jeżeli został on już 
przez niego wcześniej przeczytany, albo został przeczytany przez 
konsumenta C i na odwrót. Konsument B również nie może wielokrotnie 
czytać tego samego elementu. Ponadto, liczba elementów w buforze po 
usunięciu elementu przez dowolnego konsumenta nie może spaść poniżej 3.

Zmienne min i max nie są potrzebne - można je zastąpić buffor.size()
