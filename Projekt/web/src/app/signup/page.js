import Copyright from "@/components/Copyright";
import NextLink from 'next/link';
import { Avatar, Box, Button, Checkbox, Container, FormControlLabel, Grid, Link, TextField, Typography } from "@mui/material";
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import SignUpForm from "./SignUpForm";

export const metadata = {
  title: "Sign up - NLP Platform"
}

export default function Signin() {
  return (
    <Container maxWidth="xs" sx={{ mt: 4, mb: 4 }}>
      <Box
        sx={{
          marginTop: 8,
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
        }}
      >
        {/* <Avatar sx={{ m: 1, bgcolor: 'secondary.main' }}>
          <LockOutlinedIcon />
        </Avatar> */}
        <Typography component="h1" variant="h4">
          Sign up
        </Typography>
        <SignUpForm />
      </Box>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}