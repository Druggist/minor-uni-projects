(define
	(domain world-of-blocks)
	(:requirements :adl)
	(:predicates
		(on-top ?x ?y)
		(on-floor ?x)
		(clear ?x)
	)
        ; przesuń paczkę na podłogę
	(:action move-to-floor
		:parameters (?x ?z)
		:precondition
		(and
			(clear ?x)
			(on-top ?x ?z)
		)
		:effect
		(and
			(not (on-top ?x ?z))
			(on-floor ?x)
			(clear ?z)
		)
	)
        ; przesuń paczkę na inną paczkę
	(:action move-to-block
		:parameters (?x ?y)
		:precondition
		(and
			(clear ?x)
			(clear ?y)
		)
		:effect
		(and
			(on-top ?x ?y)
			(not (clear ?y))
			(not (on-floor ?x))
		)
	)
)