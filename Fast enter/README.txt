Данная программа показывает работу автозамены/автодополнения слов в тексте.
	Имеется автопополняемая база данных с возможными словами.
	При вводе слова программа может предложить пользователю возможное слово, так
		пользователь может сократить количество нажатий на клавиатуру к минимуму.

	Описание работы:
		При запуске программы происходит считывание базы данных.
		В первую строку необходимо ввести количество слов.
		В следующей строке пользователь вводит слова через пробел.
			В процессе ввода программа может предложить вставить слово из базы
				данных, для этого нужно нажать CTRL+p.
			Если введённого слова в базе данных нет, оно туда добавится автоматически.
		При по завершении программы происходит обновление базы данных.

	Пример работы:
		Ввод:
			3
			q<CTRL+p> door h<CTRL+p>

		Вывод:
			3
			qwerty door hello

		В процессе работы q и h дополнились до qwerty и hello соответственно, а 
			door добавилось в базу данных.