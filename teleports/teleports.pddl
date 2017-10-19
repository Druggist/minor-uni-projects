(define
	(domain teleports)
	(:requirements :adl)
	(:types planet player button lever star space)
	(:predicates
		(on ?x - object ?p1 - planet)
		(open ?l1 - lever)
		(starlock ?p1 - planet)
		(empty ?p1 - space)
		(blocking ?b1 - button ?l1 - lever)
		(one-way ?l1 - lever ?p1 ?p2 - planet)
		(two-way ?p1 ?p2 - planet)
		(two-way ?ps1 ?ps2 - space)
	)

	(:action teleport-one-way
		:parameters (?x - player ?p1 ?p2 - planet ?l1 - lever)
		:precondition
		(and
			(on ?x ?p1)
			(one-way ?l1 ?p1 ?p2)
			(open ?l1)
		)
		:effect
		(and
			(not (on ?x ?p1))
			(on ?x ?p2)
			(not (open ?l1))
		)
	)

	(:action teleport-two-way
		:parameters (?x - player ?p1 ?p2 - planet)
		:precondition
		(and
			(on ?x ?p1)
			(two-way ?p1 ?p2)
		)
		:effect
		(and
			(not (on ?x ?p1))
			(on ?x ?p2)
		)
	)

	(:action star-two-way
		:parameters (?s1 - star ?ps1 ?ps2 - space)
		:precondition
		(and
			(on ?s1 ?ps1)
			(two-way ?ps1 ?ps2)
			(empty ?ps2)
			(exists (?x - player ?p1 - planet) (and (on ?x ?p1) (starlock ?p1)))
		)
		:effect
		(and
			(not (on ?s1 ?ps1))
			(on ?s1 ?ps2)
			(empty ?ps1)
			(not (empty ?ps2))
		)
	)

	(:action pull-lever
		:parameters (?x - player ?p1 - planet ?l1 - lever ?b1 - button)
		:precondition
		(and
			(on ?x ?p1)
			(on ?l1 ?p1)
			(not (open ?l1))
			(not (blocking ?b1 ?l1))
		)
		:effect
		(and
			(open ?l1)
		)
	)

	(:action disarm-barrier
		:parameters (?x - player ?p1 - planet ?b1 - button ?l1 - lever)
		:precondition
		(and
			(on ?x ?p1)
			(on ?b1 ?p1)
			(blocking ?b1 ?l1)
		)
		:effect
		(and
			(not (blocking ?b1 ?l1))
		)
	)


)