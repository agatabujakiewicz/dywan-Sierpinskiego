# Sierpinski-s-carpet

 Temat zadania
 
Program rysuje dywan Sierpińskiego wraz z możliwością ustawienia stopnia deformacji 
dywanu.


 Opis algorytmu zastosowanego do uzyskania efektu
 
W programie została wykorzystana funkcja rekurencyjna, która w przypadku gdy 
aktualny „poziom” dywanu nie jest tym, który został wybrany, wywołuje kolejne 8 
funkcji rekurencyjnych dla aktualnego kwadratu podzielonego na 9 części z 
pominięciem środkowego kwadratu i 1/3 aktualnej długości boki. Natomiast jeśli 
żądany poziom został osiągnięty rysuje ona kwadrat za pomocą funkcji „draw”. W 
wyżej wymienionej funkcji tworzony jest obiekt typu „GL_Polygon” i przypisywane 
do niego zostają 4 wierzchołki losowo z perturbowane w zależności od ustalonego 
poziomu perturbacji oraz ustawione zostają losowe kolory.
