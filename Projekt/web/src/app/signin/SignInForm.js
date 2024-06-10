'use client'
import * as React from 'react';
import NextLink from 'next/link';
import { Avatar, Box, Button, Checkbox, Container, FormControlLabel, Grid, Link, TextField, Typography } from "@mui/material";
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import { sha512 } from 'js-sha512';
import { baseUrl } from '../lib/backend';
import { useRouter } from 'next/navigation';
import { getCookie, setCookie } from 'cookies-next'

export default function SignInForm() {
  const [auth, setAuth] = React.useState(null)
  const [isLoading, setIsLoading] = React.useState(false);
  const [error, setError] = React.useState("");

  const router = useRouter();

  const handleSubmit = (event) => {
    event.preventDefault();
    const data = new FormData(event.currentTarget);

    let email = data.get('email');
    let password = data.get('password');
    let remember = data.get('remember');

    password = sha512(password + email)

    try {
      fetch(`${baseUrl}/api/signin`, {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          email,
          password
        })
      })
        .then(res => res.json())
        .then(({ data, token }) => {
          if (token === 0) {
            setAuth(0)
            setError("Invalid email or password!")
            throw data;
          }
          setError("")
          console.log(data)
          console.log(token)
          setAuth(token)

          console.log(remember);

          if (remember === "remember") {
            setCookie(remember);
          }

          router.push("/")
        })
    } catch (err) {
      setAuth(-1)
      setError("Network error occurred! Please try again later!")
      console.error(err);
    }
  };

  return (
    <Box component="form" onSubmit={handleSubmit} sx={{ mt: 1 }}>
      <TextField
        margin="normal"
        required
        fullWidth
        id="email"
        label="Email Address"
        name="email"
        autoComplete="email"
        autoFocus
      />
      <TextField
        margin="normal"
        required
        fullWidth
        name="password"
        label="Password"
        type="password"
        id="password"
        autoComplete="current-password"
      />
      <FormControlLabel
            control={<Checkbox value="remember" name="remember" color="primary" />}
            label="Remember me"
          />
      <Button
        type="submit"
        fullWidth
        variant="contained"
        sx={{ mt: 3, mb: 2 }}
      >
        Sign In
      </Button>
      {error && (
        <Grid container justifyContent="center" sx={{ mb: 1 }}>
          <Typography variant="body2" color="error">
            {error}
          </Typography>
        </Grid>
      )}
      <Grid container>
        <Grid item xs>
          <Link href="#" variant="body2">
            Forgot password?
          </Link>
        </Grid>
        <Grid item>
          <Link href="/signup" variant="body2" component={NextLink}>
            {"Don't have an account? Sign Up"}
          </Link>
        </Grid>
      </Grid>
    </Box>
  );
}