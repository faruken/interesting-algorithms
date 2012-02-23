; Newton's Method to find square root of a number
; in Common-LISP
;
;

(defun square(x)
  (* x x))

(defun average(x y)
  (ash (+ x y) (- 1)))

(defun good-enough(guess x)
  (< (abs (- (square(guess)) x) 0.00001)))

(defun improve(guess x)
  (average(guess (/ x guess))))

(defun sqrt-inner (guess x)
  (if (good-enough (guess x)) guess
    (sqrt-inner (improve(guess x)) x)))

(defun sqrt(x)
  (sqrt-inner(1.0 x)))
