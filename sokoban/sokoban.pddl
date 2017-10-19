(define
	(domain sokoban)
	(:requirements :adl)
	(:predicates
		(poziomo ?x ?y)
		(pionowo ?x ?y)
		(robot ?x)
		(paczka ?x)
		(cel ?x)
	)

	(:action idz
		:parameters (?x ?y)
		:precondition 
		(and
			(robot ?x)
			(not (robot ?y))
			(not (paczka ?y))
			(or (poziomo ?x ?y) (pionowo ?x ?y))
		)
		:effect 
		(and
			(not (robot ?x))
			(robot ?y)
		)
	)

	(:action pchaj
		:parameters (?x ?y ?z)
		:precondition 
		(and
			(robot ?x)
			(paczka ?y)
			(not (robot ?z))
			(not (paczka ?z))
			(or (and (poziomo ?x ?y) (poziomo ?y ?z)) (and (pionowo ?x ?y) (pionowo ?y ?z))) 
		)
		:effect 
		(and
			(not (robot ?x))
			(robot ?y)
			(not (paczka ?y))
			(paczka ?z)
		)
	)
)