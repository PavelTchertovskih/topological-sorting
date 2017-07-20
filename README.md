# topological-sorting
Моя реализация задачки http://oop.afti.ru/tasks/topologicheskaya-sortirovka
Реализован класс topsort, который хранит граф зависимостей в виде map<string, pair<list<const string*>,int>> nodes;
                                                                      имя узла     список зависимостей  цвет(используется для обхода графа в глубину)
В test.cpp реализовано несколько тестов, а также функция bool verify(const vector< pair< string, vector<string> > >& input, topsort& ts), которая, принимая на вход граф зависимостей в виде вектора пар "узел - завасимости", проверяет корректность отсортированного списка узлов.
Тесты пока не включают ряд частных случаев, описанных в задачке.
