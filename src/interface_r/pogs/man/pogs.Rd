% Generated by roxygen2 (4.0.1): do not edit by hand
\name{pogs}
\alias{pogs}
\title{Proximal Operator Graph Solver}
\usage{
pogs(A, f, g, params = list())
}
\arguments{
\item{A}{Matrix encoding constraint \eqn{y = Ax}.}

\item{f}{List with fields a, b, c, d, e, and h. All fields except h are
optional and each field which is specified must be a vector of length 1 or nrow(A).}

\item{g}{List with fields a, b, c, d, e, and h. All fields except h are
optional and each field which is specified must be a vector of length 1 or ncol(A).}

\item{params}{List of parameters (rel_tol=1e-4, abs_tol=1e-4, rho=1.0,
max_iter=1000, quiet=FALSE). All parameters are optional and take on a
default value if not specified.}
}
\description{
Solver for convex optimization problems in the form
\deqn{\min. f(y) + g(x), \text{ s.t. } y = Ax}{min. f(y) + g(x),  s.t. y = Ax,}
where \eqn{f} and \eqn{g} are convex, separable, and take the form
\deqn{c h(a x - b) + d x + e x^2,} where \eqn{a}, \eqn{b} and
\eqn{d} are real, \eqn{c} and \eqn{d} are non-negative and \eqn{h} is one
of 16 convex functions (see. \link{kAbs}, \link{kExp}, \link{kHuber},
\link{kIdentity}, \link{kIndBox01}, \link{kIndEq0}, \link{kIndGe0},
\link{kIndLe0}, \link{kLogistic}, \link{kMaxNeg0}, \link{kMaxPos0},
\link{kNegEntr}, \link{kNegLog}, \link{kRecipr}, \link{kSquare}, \link{kZero}).
}
\examples{
# Specify Lasso problem.
A = matrix(rnorm(100 * 10), 100, 10)
b = rnorm(100)
lambda = 5
f = list(h = kSquare(), b = b)
g = list(h = kAbs(), c = lambda)
pogs(A, f, g)
}

