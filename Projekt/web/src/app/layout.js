import { Inter } from "next/font/google";
import "./globals.css";
import "halfmoon/css/halfmoon.min.css";

export const metadata = {
  title: "NLP Platform",
  description: "Natural Language Processing Platform",
};

export default function RootLayout({ children }) {
  return (
    <html lang="en" data-bs-core="elegant" data-bs-theme="dark">
      <body className="ps-md-sbwidth">{children}</body>
    </html>
  );
}
