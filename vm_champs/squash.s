.name       "Squash"
.comment    "I will win, if you are a banana"

    sti r1, %:shout, %1
    sub r1, r1, r2

shout:
    live %12
    zjmp %:shout
