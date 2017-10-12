(define
	(domain hanoi)
	(:requirements :adl)
	(:predicates
		(on ?k1 ?k2)
		(smaller ?k1 ?k2)
		(clear ?k1)
	)
       
	(:action move
		:parameters (?k1 ?k2 ?k3)
		:precondition
		(and
			(clear ?k1)
			(clear ?k3)
			(smaller ?k1 ?k3)
			(on ?k1 ?k2)
		)
		:effect
		(and
			(not (on ?k1 ?k2))
			(on ?k1 ?k3)
			(clear ?k2)
			(not (clear ?k3))
		)
	)
)