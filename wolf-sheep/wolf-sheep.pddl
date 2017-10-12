(define
	(domain wolf-sheep)
	(:requirements :adl)
	(:predicates
		(on ?x ?l1)
		(shore ?l1)
		(boat ?l1)
		(farmer ?x)
		(sheep ?x)
		(wolf ?x)
		(cabbage ?x)
	)
       
	(:action move-to-boat
		:parameters (?x ?y ?z ?w ?v ?l1 ?l2)
		:precondition
		(and
			(shore ?l1)
			(boat ?l2)
			(on ?x ?l1)
			(on ?y ?l1)
			(farmer ?x)
			(or
				(sheep ?y) 
				(and (farmer ?y) (sheep ?z) (wolf ?w) (cabbage ?v) (or (not (on ?z ?l1)) (not (on ?w ?l1))) (or (not (on ?z ?l1)) (not (on ?v ?l1)))) 
				(and (wolf ?y) (sheep ?z) (cabbage ?w) (or (not (on ?z ?l1)) (not (on ?w ?l1))))
				(and (cabbage ?y) (sheep ?z) (wolf ?w) (or (not (on ?z ?l1)) (not (on ?w ?l1))))
			)
		)
		:effect
		(and
			(not (on ?x ?l1))
			(not (on ?y ?l1))
			(on ?x ?l2)
			(on ?y ?l2)
		)
	)

	(:action move-from-boat
		:parameters (?x ?y ?z ?w ?v ?l1 ?l2)
		:precondition
		(and
			(shore ?l2)
			(boat ?l1)
			(on ?x ?l1)
			(on ?y ?l1)
			(farmer ?x)
			(or
				(and (sheep ?y) (cabbage ?z) (wolf ?w) (not (on ?z ?l1)) (not (on ?w ?l1)))
				(and (cabbage ?y) (sheep ?z) (wolf ?w) (not (on ?z ?l1)) (not (on ?w ?l1)))
				(and (wolf ?y) (sheep ?z) (cabbage ?w) (not (on ?z ?l1)) (not (on ?w ?l1)))
				(and (farmer ?y) (sheep ?z) (wolf ?w) (cabbage ?v) (not (on ?z ?l1)) (not (on ?w ?l1)) (not (on ?v ?l1)))
			)
		)
		:effect
		(and
			(not (on ?x ?l1))
			(not (on ?y ?l1))
			(on ?x ?l2)
			(on ?y ?l2)
		)
	)	
)